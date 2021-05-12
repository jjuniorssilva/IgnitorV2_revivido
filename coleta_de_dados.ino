void coletarDados(){ // essa funcção centraliza as requisições de dados 
  cap_carga = coletarCargaCap();
  //empuxo = coletarEmpuxo();
  bateria = coletarBateria();
}

/*unsigned long  coletarEmpuxo(){ // quando chamada solicita a celular de carga que retorne uma medição base
  unsigned long Count = 0;
  unsigned char i;

  digitalWrite(ADSK, LOW);
  while (digitalRead(ADDO));

  for (i = 0; i < 24; i++)
  {
    digitalWrite(ADSK, HIGH);
    Count = Count << 1;
    digitalWrite(ADSK, LOW);
    if (digitalRead(ADDO)) Count++;

  } //end for

  digitalWrite(ADSK, HIGH);
  Count = Count ^ 0x800000;
  digitalWrite(ADSK, LOW);
  return Count;
} */
int coletarCargaCap(){ // quando chamado faz a leitura do pin_carga e mapeia 
  return  map(analogRead(pin_coleta_carga), 0, 840, 0, 100);// 840 é o valor aproximado para correcao da tensao
}
int coletarBateria(){// quando chamado faz a leitura do pin_bateria e mapeia 
  return  map(analogRead(pin_coleta_bateria), 0, 840, 0, 100);// Ajustar caso for usar
}
