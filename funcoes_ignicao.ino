void ignitar(){ // quando chamada liberar a carga para o squib
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("PRD");
  lcd.setCursor(0, 1);
  lcd.print("Ignicao!!!");
  digitalWrite(pin_ig, HIGH);
  notifyClients("IG=-1");
  delay(500);
  digitalWrite(pin_ig, LOW);
  updateDisplayData();
}
void cont_reg(long time_atual){ // quando é chamada inicia a contagem regressiva para a ignição
  if(time_atual-aux_contagem>1100 && contagem==true){
    notifyClients("CONT_IG="+String(time_cont));
    lcd.setCursor(10, 2);
    lcd.print(String(time_cont)+" "); 
    time_cont--;
    aux_contagem=time_atual;
    if(time_cont<0){
      ignitar();
      contagem=false;
      time_cont=10;
    }
  }
}
