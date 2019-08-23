//Código pro Arduino
//Mensagem:
//a - Turma "A" apertou o botão
//A - Turma "A" soltou o botão

const int ledPin = 13;

//Botão da turma
const int bt[] = {2,3,4,5,6,7};

//Estado da turma, antes e depois
bool sa[] = {0,0,0,0,0,0};
bool sd[] = {0,0,0,0,0,0};


void setup() {
    int i;
    
    pinMode(ledPin, OUTPUT);
    for(i=0;i<6;i++)
        pinMode(bt[i], INPUT);

    Serial.begin(9600);
}


void loop(){
	int i;

	//Grava todos os estados para não ter mudança durante
	for(i=0;i<6;i++)
		sd[i] = digitalRead(bt[i]);

	//Vê se teve mudança
	for(i=0;i<6;i++){
		if(!sa[i] && sd[i])
			Serial.print((char)('A'+i));
		else if(sa[i] && !sd[i])
			Serial.print((char)('a'+i));
		sa[i] = sd[i];
	}

        delay(1); //1ms
}
