##                                                           LABORATORIO 5
# EJERCICIO 4
# 4. Using SSH modify the motor’s duty cycle. How can we use PWM in
#raspberry pi? Explain the steps.
## EJERCICIO 5

## 5. When a button is pressed on the Raspberry a message “buzzer” must be
##send to the Tiva.


from gpiozero import LED, Buzzer
from time import sleep

# Definir los pines para el LED y el Buzzer
led = LED(17)  # Suponiendo que el LED está en el pin GPIO 17
buzzer = Buzzer(18)  # Suponiendo que el buzzer está en el pin GPIO 18

while True:
    try:
        # Solicitar al usuario que ingrese un valor
        print("\nOpciones:")
        print("1 - Encender LED")
        print("2 - Apagar LED")
        print("3 - Encender Buzzer")
        print("4 - Apagar Buzzer")
        print("5 - Salir")
        
        choice = int(input("Ingrese su opción: "))

        if choice == 1:
            led.on()
            print("LED encendido")
        elif choice == 2:
            led.off()
            print("LED apagado")
        elif choice == 3:
            buzzer.on()
            print("Buzzer encendido")
        elif choice == 4:
            buzzer.off()
            print("Buzzer apagado")
        elif choice == 5:
            print("Saliendo...")
            break
        else:
            print("Opción no válida. Ingrese un número entre 1 y 5.")
        
        sleep(1)  # Esperar 1 segundo antes de permitir otra entrada
        
    except ValueError:
        print("Por favor, ingrese un número válido.")
