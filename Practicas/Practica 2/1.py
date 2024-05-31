class Usuario:
    def __init__(self, nombre_usuario, id_usuario, saldo):
        self.nombre_usuario = nombre_usuario
        self.id_usuario = id_usuario
        self.saldo = saldo
        self.cuentas = []

    def agregar_cuenta(self, cuenta):
        self.cuentas.append(cuenta)

class Cuenta:
    def __init__(self):
        # Aquí puedes inicializar los atributos de la cuenta si es necesario
        pass

def crear_cuenta():
    nombre_usuario = input("Ingrese el nombre del usuario: ")
    id_usuario = input("Ingrese el ID del usuario: ")
    saldo_inicial = float(input("Ingrese el saldo inicial de la nueva cuenta: "))
    nuevo_usuario = Usuario(nombre_usuario, id_usuario, saldo_inicial)
    nueva_cuenta = Cuenta()
    return nuevo_usuario, nueva_cuenta

def mostrar_menu():
    print("Menú:")
    print("1- Dar de alta una cuenta")
    print("2- Transferir")
    print("3- Depositar")
    print("4- Retirar")
    print("5- Mostrar Cuenta")
    print("6- Salir")

def depositar():
    id_usuario = input("Ingrese el ID de usuario: ")
    monto = float(input("Ingrese el monto a depositar: "))

    usuario_encontrado = False
    for usuario in usuarios:
        if usuario.id_usuario == id_usuario:
            usuario_encontrado = True
            usuario.saldo += monto
            print("Depósito realizado con éxito.")
            break

    if not usuario_encontrado:
        print("No se encontró el usuario con el ID proporcionado.")

def transferir():
    id_origen = input("Ingrese el ID de origen de la cuenta: ")
    id_destino = input("Ingrese el ID de destino de la cuenta: ")
    monto = float(input("Ingrese el monto a transferir: "))
  


    usuario_origen = None
    usuario_destino = None

    for usuario in usuarios:
        if usuario.id_usuario == id_origen:
            usuario_origen = usuario
        elif usuario.id_usuario == id_destino:
            usuario_destino = usuario

    if usuario_origen is None:
        print("El usuario de origen no existe.")
    elif usuario_destino is None:
        print("El usuario de destino no existe.")
    elif usuario_origen.saldo < monto:
        print("Saldo insuficiente para realizar la transferencia.")
    else:
        usuario_origen.saldo -= monto
        usuario_destino.saldo += monto
        print("Transferencia realizada con éxito.")

def mostrar_cuenta():
    id_usuario = input("Ingrese el ID de usuario: ")
    usuario_encontrado = False
    for usuario in usuarios:
        if usuario.id_usuario == id_usuario:
            usuario_encontrado = True
            print("==============================")
            print(f"Nombre de usuario: {usuario.nombre_usuario}")
            print(f"ID de usuario: {usuario.id_usuario}")
            print(f"Saldo de la cuenta: {usuario.saldo}")
            print("==============================")
            break
    if not usuario_encontrado:
        print("No se encontró el usuario con el ID proporcionado.")

def retirar():
    id_usuario = input("Ingrese el ID de usuario: ")
    monto = float(input("Ingrese el monto a retirar: "))

    usuario_encontrado = False
    for usuario in usuarios:
        if usuario.id_usuario == id_usuario:
            usuario_encontrado = True
            if usuario.saldo < monto:
                print("Saldo insuficiente para realizar el retiro.")
            else:
                usuario.saldo -= monto
                print("Retiro realizado con éxito.")
            break

    if not usuario_encontrado:
        print("No se encontró el usuario con el ID proporcionado.")

def Dar_De_Alta_Cuenta():
    nuevo_usuario, nueva_cuenta = crear_cuenta()
    usuarios.append(nuevo_usuario)
    nuevo_usuario.agregar_cuenta(nueva_cuenta)
    print("Cuenta creada exitosamente.")

usuarios = []

while True:
    mostrar_menu()
    opcion = input("Seleccione una opción (1/2/3/4/5/6): ")

    if opcion == "1":
        Dar_De_Alta_Cuenta()

    elif opcion == "2":
        transferir()

    elif opcion == "3":
        depositar()

    elif opcion == "4":
        retirar()

    elif opcion == "5":
        mostrar_cuenta()

    elif opcion == "6":
        print("Gracias por utilizar nuestro sistema. ¡Hasta luego!")
        break

    else:
        print("Opción no válida. Por favor, seleccione una opción válida (1/2/3/4/5/6).")
