#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

void gameConfig();
void classicGame(unsigned int Jugadores, unsigned int Rondas, string Dificultad);
void sprite(int stage);

int main()
{
	unsigned int option = 0;
	while (option != 2)
	{
		system("cls");
		cout << "Bienvenidos al juego del ahorcado" << endl;
		cout << " " << endl;
		cout << "1) Jugar                  2)Salir" << endl;
		cin >> option;
		switch (option)
		{
		case 1:
			gameConfig();
			break;
		case 2:
			system("cls");
			cout << "Adios" << endl;
			break;
		default:
			cout << "Opcion no valida" << endl;
			break;
		}
	}

}

void gameConfig()
{
	unsigned int option = 10;
	unsigned int Jugadores = 1;
	unsigned int Rondas = 1;
	string Dificultad = "Normal";
	string ModoDeJuego = "Clasico";
	string cualquierCosa;

	while (option != 0 && option != 5)
	{
		system("cls");
		cout << "Configuracion del juego actual:" << endl;
		cout << "(si quiere cambiar algo, escriba el numero de la opcion que quiera cambiar)" << endl;
		cout << " " << endl;
		cout << "1) Jugadores: " << Jugadores << endl;
		cout << "2) Rondas: " << Rondas << endl;
		cout << "3) Dificultad: " << Dificultad << endl;
		cout << "4) Modo de juego: " << ModoDeJuego << endl;
		cout << " " << endl;
		cout << "0) Jugar                                                          5) Volver" << endl;
		cin >> option;
		switch (option)
		{
		case 0:
			if (ModoDeJuego == "Clasico")
			{
				classicGame(Jugadores, Rondas, Dificultad);
			}
			// else if(ModoDeJuego == "Battle Royale xdxd")
			break;
		case 1:
			option = 10;
			while (option != 1 && option != 2)
			{
				system("cls");
				cout << "Elija el tipo de juego" << endl;
				cout << " " << endl;
				cout << "1) Un Jugador  2) Multijugador" << endl;
				cin >> option;
				switch (option)
				{
				case 1:
					Jugadores = 1;
					break;
				case 2:
					Jugadores = 1;
					while (Jugadores <= 1)
					{
						system("cls");
						cout << "Escriba el numero de jugadores" << endl;
						cin >> Jugadores;
					}
					break;
				default:
					cout << "Opcion no valida" << endl;
					break;
				}
			}
			break;
		case 2:
			do
			{
				system("cls");
				cout << "Escriba el numero de rondas que quiera jugar" << endl;
				cin >> Rondas;
				//se supone que el while de abajo evita que haya rondas negativas, pero al ser la variable Rondas usigned int, si pones negativas te pondra un numero muy grande
				//podria hacerla int normal, o usar alguna variable extra junto con un if, pero de mientras le dejare asi, ya que no afecta demasiado al juego (creo)
			} while (Rondas <= 0);
			break;
		case 3:
			option = 10;
			while (option != 1 && option != 2 && option != 3)
			{
				system("cls");
				cout << "Elija la dificultad del juego" << endl;
				cout << " " << endl;
				cout << "1) Facil" << endl;//da una pista cada 4 turnos
				cout << "2) Normal" << endl;//normal
				cout << "3) Dificil" << endl;//el muñeco avanza mas rapido
				cout << "4) Extremo" << endl;//el muñeco se conserva al pasar las rondas
				cin >> option;
				switch (option)
				{
				case 1:
					Dificultad = "Facil";
					break;
				case 2:
					Dificultad = "Normal";
					break;
				case 3:
					Dificultad = "Dificil";
					break;
				case 4:
					Dificultad = "Extremo";
					break;
				default:
					cout << "Opcion no valida" << endl;
					break;
				}
			}
			break;
		case 4:
			cout << "Lo siento, el que hizo este juego se alucino y no midio sus capacidades, asi que por ahora solo hay 1 modo de juego" << endl;
			cout << "(Escriba cualquier cosa para continuar)" << endl;
			cin >> cualquierCosa;
			break;
		case 5:
			cout << "Adios" << endl;
			break;
		default:
			cout << "Opcion no valida" << endl;
			break;
		}
	}
}

void classicGame(unsigned int Jugadores, unsigned int Rondas, string Dificultad)
{
	vector<string> palabrasFaciles =
	{
		"GATO",
		"LINUX",
		"PERRO",
		"CACA",
		"CASA",
		"PATO",
		"PIE",
		"ROCA",
		"COCA",
		"COLA"
	};
	vector<string> palabrasNormales =
	{
		"BARBARO",
		"MOCHILA",
		"FAMILIA",
		"PERSONA",
		"BOTELLA",
		"MACETA",
		"GIRASOL",
		"CASTILLO",
		"LABRADOR",
		"MAESTRO",
		"ESCUELA"
	};
	vector<string> palabrasDificiles =
	{
		"DEFENESTRAR",
		"REFRIGERADOR",
		"MICROONDAS",
		"HOMICIDIO",
		"SUPERCALIFRAGILISTOESPIRALIDOSO",
		"ELECTRICIDAD"
	};
	vector<char> ban =
	{
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'!',
		'.',
		',',
		'#',
		'$',
		'%',
		'-'
	};
	vector<char> palabraEnPantalla;
	char letraJugador;
	string adivinaElJugador;
	bool victoria = false;
	bool derrota = false;
	int stage = 0;
	bool huboLetra = false;
	bool hayGuion = false;
	bool usoLetraUsada = false;
	vector<int> puntuaciones(Jugadores, 0);
	string cualquierCosa = "hola";
	string palabraJugador;
	int turnoJugadoresEscribir = 1;
	int turnoJugadoresAdivinar = 1;
	vector<char> palabrasUsadas;

	srand(time(NULL));
	int randomNumber = rand();
	int wordsRandomIndex = (randomNumber % palabrasNormales.size());
	int cuanto;
	int turno = 0;


	for (int i = 0; i < Rondas; i++)
	{
		//General para empezar
		if (i > 0)
		{
			turno = 0;
			victoria = false;
			derrota = false;
			if (Dificultad != "Extremo")
			{
				stage = 0;
			}
			cuanto = palabraEnPantalla.size();
			for (int j = 0; j != cuanto; j++)
			{
				palabraEnPantalla.erase(palabraEnPantalla.begin());
			}
			cuanto = palabrasUsadas.size();
			for (int j = 0; j != cuanto; j++)
			{
				palabrasUsadas.erase(palabrasUsadas.begin());
			}
			//cout << palabraEnPantalla.size() << endl;
			//cin >> cualquierCosa;
		}

		if (Jugadores == 1)
		{
			//Generamos numero aleatorio
			randomNumber = rand();
			wordsRandomIndex = (randomNumber % palabrasNormales.size());

			//Aqui abajo ponemos los espacios
			for (int j = 0; j != palabrasNormales[wordsRandomIndex].size(); j++)
			{
				palabraEnPantalla.push_back('_');
			}
		}
		else
		{
			system("cls");
			cout << "RONDA #" << i + 1 << endl;
			cout << " " << endl;
			cout << "Antes de empezar, que el jugador #" << turnoJugadoresEscribir << " escriba la palabra para adivinar" << endl;
			turnoJugadoresEscribir++;
			if (turnoJugadoresEscribir > Jugadores)
			{
				turnoJugadoresEscribir = 1;
			}
			cout << "(Asegurate de que los otros jugadores no vean la palabra)" << endl;
			cin >> palabraJugador;
			transform(palabraJugador.begin(), palabraJugador.end(), palabraJugador.begin(), ::toupper);
			for (int j = 0; j != palabraJugador.size(); j++)
			{
				palabraEnPantalla.push_back('_');
			}
		}


		while (victoria == false && derrota == false)
		{
			system("cls");
			cout << "RONDA #" << i + 1 << endl;
			if (Jugadores == 1)
			{
				cout << "Puntuacion: " << puntuaciones[0] << endl;
			}
			cout << " " << endl;
			sprite(stage);
			cout << " " << endl;
			//Aqui escribimos los espacios
			for (int j = 0; j != palabraEnPantalla.size(); j++)
			{
				cout << palabraEnPantalla[j] << " ";
			}

			//Aqui pedimos letra
			cout << " " << endl;
			cout << " " << endl;
			if (Jugadores == 1)
			{
				cout << "Escriba la letra para adivinar" << endl;
			}
			else
			{
				if (turnoJugadoresAdivinar == turnoJugadoresEscribir - 1)
				{
					turnoJugadoresAdivinar++;
				}
				if (turnoJugadoresAdivinar > Jugadores)
				{
					turnoJugadoresAdivinar = 1;
					if (turnoJugadoresAdivinar == turnoJugadoresEscribir - 1)
					{
						turnoJugadoresAdivinar++;
					}
				}
				cout << "Turno del jugador #" << turnoJugadoresAdivinar << " para escribir la letra para adivinar" << endl;
				turnoJugadoresAdivinar++;
			}
			cout << "(Si quieres intentar adivinar toda la palabra de una, escribe 1)" << endl;
			//letras usadas
			cout << " " << endl;
			cout << "Letras Usadas: ";
			for (int j = 0; j != palabrasUsadas.size(); j++)
			{
				cout << palabrasUsadas[j] << ", ";
			}
			cout << " " << endl;
			//cout << "(En mayusculas)" << endl;
			do
			{
				usoLetraUsada = false;
				cin >> letraJugador;
				if (letraJugador == '1')
				{
					system("cls");
					cout << "Escribe la palabra completa" << endl;
					cin >> adivinaElJugador;
					transform(adivinaElJugador.begin(), adivinaElJugador.end(), adivinaElJugador.begin(), ::toupper);
					if (Jugadores == 1)
					{
						if (adivinaElJugador == palabrasNormales[wordsRandomIndex])
						{
							victoria = true;
						}
					}
					else
					{
						if (adivinaElJugador == palabraJugador)
						{
							victoria = true;
						}
					}
				}
				else
				{
					//Aqui validamos
					/*
					Se supone que lo de abajo evita que sea string, al checar que el tamaño del char no pase de 1
					if (letraJugador.size() > 1)
					{
						cout << "No puedes poner un string completo" << endl;
						cin >> cualquierCosa;
						usoLetraUsada = true;
					}
					*/
					for (int j = 0; j != ban.size(); j++)
					{
						if (letraJugador == ban[j])
						{
							cout << "Ese caracter no es valido" << endl;
							usoLetraUsada = true;
						}
					}
					letraJugador = toupper(letraJugador);
					//Aqui checamos que no haya sido usada
					for (int j = 0; j != palabrasUsadas.size(); j++)
					{
						if (letraJugador == palabrasUsadas[j])
						{
							cout << "No puedes usar una letra ya usada" << endl;
							usoLetraUsada = true;
						}
					}

				}
			} while (usoLetraUsada == true);
			if (letraJugador != '1')
			{
				palabrasUsadas.push_back(letraJugador);
			}


			//transform(letraJugador.begin(), letraJugador.end(), letraJugador.begin(), ::toupper);



			//Aqui checamos si esta la letra
			huboLetra = false;
			if (Jugadores == 1)
			{
				for (int j = 0; j != palabrasNormales[wordsRandomIndex].size(); j++)
				{
					if (letraJugador == *(palabrasNormales[wordsRandomIndex].begin() + j))
					{
						palabraEnPantalla[j] = letraJugador;
						huboLetra = true;
					}
				}
			}
			else
			{
				for (int j = 0; j != palabraJugador.size(); j++)
				{
					if (letraJugador == *(palabraJugador.begin() + j))
					{
						palabraEnPantalla[j] = letraJugador;
						huboLetra = true;
						puntuaciones[turnoJugadoresAdivinar - 2]++;

					}
				}
			}

			//Aqui checamos si se equivoco
			if (huboLetra == false)
			{
				if (Dificultad == "Dificil" || Dificultad == "Extremo")
				{
					stage = stage + 2;
				}
				else
				{
					stage++;
				}
				if (stage == 15)
				{
					derrota = true;
				}
			}
			//Aqui checamos si aun quedan guiones en la palabra
			hayGuion = false;
			for (int j = 0; j != palabraEnPantalla.size(); j++)
			{
				if (palabraEnPantalla[j] == '_')
				{
					hayGuion = true;
				}
			}
			//Aqui checamos si ya termino la palabra
			if (hayGuion == false)
			{
				victoria = true;
			}

			if (Dificultad == "Facil")
			{
				turno++;
				if (turno == 5)
				{
					if (Jugadores == 1)
					{
						for (int j = 0; j != palabraEnPantalla.size(); j++)
						{
							if (palabraEnPantalla[j] == '_')
							{
								turno = j;
								break;
							}
						}
						for (int j = 0; j != palabrasNormales[wordsRandomIndex].size(); j++)
						{
							if (*(palabrasNormales[wordsRandomIndex].begin() + turno) == *(palabrasNormales[wordsRandomIndex].begin() + j))
							{
								palabraEnPantalla[j] = *(palabrasNormales[wordsRandomIndex].begin() + turno);
								palabrasUsadas.push_back(*(palabrasNormales[wordsRandomIndex].begin() + turno));
							}
						}
					}
					else
					{
						for (int j = 0; j != palabraEnPantalla.size(); j++)
						{
							if (palabraEnPantalla[j] == '_')
							{
								turno = j;
								break;
							}
						}
						for (int j = 0; j != palabraJugador.size(); j++)
						{
							if (*(palabraJugador.begin() + turno) == *(palabraJugador.begin() + j))
							{
								palabraEnPantalla[j] = *(palabraJugador.begin() + turno);
								palabrasUsadas.push_back(*(palabraJugador.begin() + turno));
							}
						}
					}
					turno = 0;
				}
			}
		}
		if (victoria == true)
		{
			if (Jugadores == 1)
			{
				system("cls");
				cout << "ACERTASTE LA PALABRA!!" << endl;
				sprite(stage);
				cout << "+1 Punto" << endl;
				puntuaciones[0]++;
				cout << "(Escriba cualquier cosa para continuar)" << endl;
				cin >> cualquierCosa;
			}
			else
			{
				system("cls");
				cout << "EL JUGADOR #" << turnoJugadoresAdivinar - 1 << " HA COMPLETADO LA PALABRA!!" << endl;
				sprite(stage);
				cout << "El jugador recibio +3 puntos extra" << endl;
				puntuaciones[turnoJugadoresAdivinar - 2] = puntuaciones[turnoJugadoresAdivinar - 2] + 3;
				cout << "(Escriban cualquier cosa para continuar)" << endl;
				cin >> cualquierCosa;
			}
		}
		else if (derrota == true)
		{
			if (Jugadores == 1)
			{
				system("cls");
				cout << "HAS PERDIDO!!" << endl;
				sprite(15);
				cout << "La palabra era: " << palabrasNormales[wordsRandomIndex] << endl;
				cout << "(Escriba cualquier cosa para continuar)" << endl;
				cin >> cualquierCosa;
			}
			else
			{
				system("cls");
				cout << "Nadie adivino la palabra" << endl;
				sprite(15);
				cout << "El jugador #" << turnoJugadoresEscribir - 1 << " recibe +" << Jugadores - 1 << " puntos" << endl;
				puntuaciones[turnoJugadoresEscribir - 2] = puntuaciones[turnoJugadoresEscribir - 2] + (Jugadores - 1);
				cout << "(Escriban cualquier cosa para continuar)" << endl;
				cin >> cualquierCosa;
			}
		}
		if (Jugadores != 1)
		{
			system("cls");
			cout << "PUNTUACIONES" << endl;
			cout << " " << endl;
			for (int j = 0; j < Jugadores; j++)
			{
				cout << "Jugador #" << j + 1 << " tiene " << puntuaciones[j] << " puntos" << endl;
			}
			cout << "(Escriban cualquier cosa para continuar)" << endl;
			cin >> cualquierCosa;
		}
	}
	system("cls");
	cout << "JUEGO TERMINADO" << endl;
	cout << " " << endl;
	if (Jugadores == 1)
	{
		cout << "Tu puntuacion fue de: " << puntuaciones[0] << " puntos" << endl;
		cout << "(Escriba cualquier cosa para continuar)" << endl;
		cin >> cualquierCosa;
	}
	else
	{
		cout << "PUNTUACIONES" << endl;
		cout << " " << endl;
		for (int j = 0; j < Jugadores; j++)
		{
			cout << "Jugador #" << j + 1 << " tiene " << puntuaciones[j] << " puntos" << endl;
		}
		cout << "(Escriban cualquier cosa para continuar)" << endl;
		cin >> cualquierCosa;
	}

}

void sprite(int stage)
{
	switch (stage)
	{
	case 0:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 1:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 2:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0       |                " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 3:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 4:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |          |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 5:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 6:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |                 ___| |___                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 7:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |     ,______________| |___                  " << endl;
		cout << "     |  |     '-----------|       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 8:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |     ,______________| |_______________,     " << endl;
		cout << "     |  |     '-----------|       |------------'     " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 9:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |     ,______________| |_______________,     " << endl;
		cout << "     |  |     '-----------|       |------------'     " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                  | |                       " << endl;
		cout << "     |  |                  | |                       " << endl;
		cout << "     |  |                  | |                       " << endl;
		cout << "     |  |                  | |                       " << endl;
		cout << "     |  |                  | |                       " << endl;
		cout << "     |  |                  |_|                       " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 10:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |                 \\________/                 " << endl;
		cout << "     |  |     ,______________| |_______________,     " << endl;
		cout << "     |  |     '-----------|       |------------'     " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  |_| |_|                   " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 11:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |   __            \\________/                 " << endl;
		cout << "     |  | __\\ \\______________| |_______________,     " << endl;
		cout << "     |  | \\____-----------|       |------------'     " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  |_| |_|                   " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 12:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |   __            \\________/            __   " << endl;
		cout << "     |  | __\\ \\______________| |_______________/ /__ " << endl;
		cout << "     |  | \\____-----------|       |-----------_____/ " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  |_| |_|                   " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 13:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |   __            \\________/            __   " << endl;
		cout << "     |  | __\\ \\______________| |_______________/ /__ " << endl;
		cout << "     |  | \\____-----------|       |-----------_____/ " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |               ___| | |_|                   " << endl;
		cout << "     |  |              /_____|                       " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 14:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  0    0  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  -____-  |                " << endl;
		cout << "     |  |   __            \\________/            __   " << endl;
		cout << "     |  | __\\ \\______________| |_______________/ /__ " << endl;
		cout << "     |  | \\____-----------|       |-----------_____/ " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |               ___| | | |___                " << endl;
		cout << "     |  |              /_____| |_____\\               " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	case 15:
		cout << "     _________________________________               " << endl;
		cout << "     |  _____________________________|               " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                      |                     " << endl;
		cout << "     |  |                  ____^___                  " << endl;
		cout << "     |  |                 /        \\                 " << endl;
		cout << "     |  |                |  X    X  |                " << endl;
		cout << "     |  |                |    C     |                " << endl;
		cout << "     |  |                |  _----_  |                " << endl;
		cout << "     |  |   __            \\________/            __   " << endl;
		cout << "     |  | __\\ \\______________| |_______________/ /__ " << endl;
		cout << "     |  | \\____-----------|       |-----------_____/ " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |       |                  " << endl;
		cout << "     |  |                 |_______|                  " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |                  | | | |                   " << endl;
		cout << "     |  |               ___| | | |___                " << endl;
		cout << "     |  |              /_____| |_____\\               " << endl;
		cout << "     |  |                                            " << endl;
		cout << "     |  |                                            " << endl;
		cout << "_____|  |________________________________            " << endl;
		cout << "|                                       |            " << endl;
		cout << "|_______________________________________|            " << endl;
		break;
	default:
		break;
	}
}