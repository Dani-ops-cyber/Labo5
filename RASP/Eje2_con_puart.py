import time
import serial as sl
from gpiozero import OutputDevice

# Configuración del puerto serial para la Tiva
ser1 = sl.Serial("/dev/ttyACM0", 9600)
ser1.reset_input_buffer()

# Configuración de los pines para el puente H
motor1_forward = OutputDevice(17)  # Pin para avanzar motor 1
motor1_backward = OutputDevice(27)  # Pin para retroceder motor 1
motor2_forward = OutputDevice(22)  # Pin para avanzar motor 2
motor2_backward = OutputDevice(23)  # Pin para retroceder motor 2

# Variables de estado
motor1_running = False
motor2_running = False
last_command_time = time.time()

# Funciones para controlar los motores
def motor1_forward_action():
    global motor1_running
    motor1_forward.on()
    motor1_backward.off()
    motor1_running = True
    print("Motor 1 encendido")

def motor2_forward_action():
    global motor2_running
    motor2_forward.on()
    motor2_backward.off()
    motor2_running = True
    print("Motor 2 encendido")

def stop_motors():
    motor1_forward.off()
    motor2_forward.off()
    print("Motores detenidos.")

while True:
    try:
        # Verifica si hay datos disponibles
        if ser1.in_waiting > 0:
            print("Datos disponibles en el puerto serial.")
            data_raw = ser1.readline()  # Lee los bytes crudos
            print(f"Bytes crudos recibidos: {data_raw}")
            
            # Intenta decodificar los datos
            try:
                recievetiva = data_raw.decode('utf-8').rstrip()
                print("TIVA DICE: ", recievetiva)

                # Lógica para controlar los motores
                if recievetiva == "MOTOR1":
                    motor1_forward_action()
                elif recievetiva == "MOTOR2":
                    motor2_forward_action()
                elif recievetiva == "STOP":
                    stop_motors()
                
                # Actualizar el tiempo del último comando recibido
                last_command_time = time.time()

            except UnicodeDecodeError:
                print("Error al decodificar los datos recibidos.")
        else:
            print("Esperando datos de la Tiva...")

        # Comprobar si se debe detener los motores
        if time.time() - last_command_time > 2:  # Detener después de 2 segundos sin recibir un comando
            if motor1_running or motor2_running:
                stop_motors()
                motor1_running = False
                motor2_running = False

        time.sleep(1)

    except Exception as e:
        print(f"Error: {e}")

