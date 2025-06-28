//Inicializando trabajo de laboratorio
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', 'X'},
  {'1', '2', '3', '-'},
  {'P', '0', '=', '+'}
};
byte rowPins[ROWS] = {12, 11, 8, 7}; //Filas(pines del 7,8 y 12, 13)
byte colPins[COLS] = {6, 5, 4, 2}; //Columnas (pines del 2, 4 al 6)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Bienvenido! Para iniciar juego oprima 1, para ver reglas oprima 2");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '1':
        jugarJuego();
        break;
      case '2':
        mostrarReglas();
        break;
      default:
        Serial.println("Ha oprimido una opcion incorrecta");
        break;
    }
  }
}

void mostrarPuntaje(int puntosJugador, int puntosMaquina) {
  Serial.print("Jugador: ");
  Serial.print(puntosJugador);
  Serial.print(" Maquina: ");
  Serial.println(puntosMaquina);
}

void jugarJuego() {
  Serial.println("Comencemos!");
  int puntosJugador = 0,
      puntosMaquina = 0;
  bool fueronOpcionesVistas = false;
  mostrarPuntaje(puntosJugador, puntosMaquina);
  while (puntosJugador != 3 && puntosMaquina != 3) {

    char newkey = keypad.getKey();

    if (!fueronOpcionesVistas) {
      Serial.println(" ");
      Serial.println("Elige una opcion:");
      mostrarOpciones();
      fueronOpcionesVistas = true;
    }

    if (newkey) {

      char eleccionMaquina = random(1, 4) + '0'; // '1', '2' o '3'
      Serial.println(" ");
      Serial.println("***********************************************");
      if (newkey == '1') Serial.print("El Jugador eligio PIEDRA ");
      else if (newkey == '2') Serial.print("El Jugador eligio PAPEL ");
      else if (newkey == '3') Serial.print("El Jugador eligio TIJERAS ");

      if (newkey == '1' || newkey == '2' || newkey == '3') { // Hacemos este condicional para evitar que se muestre la opcion de la maquina si el jugador no eligio correctamente.
        if (eleccionMaquina == '1') Serial.println("Y la Maquina eligio PIEDRA.");
        else if (eleccionMaquina == '2') Serial.println("Y la Maquina eligio PAPEL.");
        else if (eleccionMaquina == '3') Serial.println("Y la Maquina eligio TIJERAS.");
      } else {
        Serial.println("Elegiste una opcion invalida, vuelve a intentarlo.");
      }

      if (newkey == eleccionMaquina) {
        Serial.println(" ");
        Serial.println("EMPATE!");
        Serial.println(" ");
      } else if (
        (newkey == '1' && eleccionMaquina == '3') || // Piedra gana a Tijeras
        (newkey == '2' && eleccionMaquina == '1') || // Papel gana a Piedra
        (newkey == '3' && eleccionMaquina == '2')    // Tijeras gana a Papel
      ) {
        Serial.println(" ");
        Serial.println("GANASTE!");
        Serial.println(" ");
        puntosJugador++;
      } else if (
        (newkey == '1' && eleccionMaquina == '2') || // Piedra gana a Tijeras
        (newkey == '2' && eleccionMaquina == '3') || // Papel gana a Piedra
        (newkey == '3' && eleccionMaquina == '1')    // Tijeras gana a Papel
      )
      {
        Serial.println(" ");
        Serial.println("PERDISTE!");
        Serial.println(" ");
        puntosMaquina++;
      }
      fueronOpcionesVistas = false;
      mostrarPuntaje(puntosJugador, puntosMaquina);
    }
  }
  if (puntosJugador == 3) {
    Serial.println(" ");
    Serial.println("******** FELICITACIONES, HAS GANADO EL JUEGO! ********");
  } else {
    Serial.println(" ");
    Serial.println("******** LAMENTABLEMENTE TE HA TOCADO PERDER EL JUEGO :( ********");
  }
  Serial.println(" ");
  Serial.println("Para volver a jugar oprima 1, para ver las reglas oprima 2");
}
void mostrarReglas() {
  Serial.println(" ");
  Serial.println("REGLAS DEL JUEGO:");
  Serial.println("En Piedra, Papel o Tijeras te enfrentaras a la maquina.");
  Serial.println("Ambos elegiran al mismo tiempo entre piedra, papel o tijeras.");
  Serial.println("La piedra aplasta a las tijeras, las tijeras cortan al papel y el papel envuelve a la piedra.");
  Serial.println("Si los dos eligen lo mismo, el resultado sera un empate");
  Serial.println("Ganara quien llegue primero a 3 puntos");
  Serial.println("Para elegir piedra debes oprimir 1, para Papel 2 y para Tijeras 3");
  Serial.println("Elige con cuidado y trata de vencer a la maquina!");
  Serial.println(" ");
  Serial.println("Para iniciar juego oprima 1, para ver reglas oprima 2");
}
void mostrarOpciones() {
  Serial.println("1- Piedra");
  Serial.println("2- Papel");
  Serial.println("3- Tijeras");
}
