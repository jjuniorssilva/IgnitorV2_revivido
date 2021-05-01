void armazenarDados(long time_atual){ // quando chmada faz uma gravação no sd com os dados coletados
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if(dataFile){
    dataFile.print(time_atual+" - "+empuxo);  
    dataFile.print("\t");   
    dataFile.close();
  }else{
    Serial.println("error opening datalog.txt");
  }
}
