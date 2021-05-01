void updateDisplayData(){ // quando é chamada atualizar o diisplay com os dados coletados
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("PRD");
  lcd.setCursor(0, 1);
  lcd.print("BAT:");
  lcd.setCursor(0, 2);
  lcd.print("CAP:");
  lcd.setCursor(0, 3);
  lcd.print("EMP:");
  
  lcd.setCursor(4, 1);
  lcd.print(String(bateria)+"%");
  lcd.setCursor(4, 2);
  lcd.print(String(cap_carga)+"%");
  lcd.setCursor(4, 3);
  lcd.print(String((-0.0002264*empuxo) + 1877.7218)+"Kg");
}
void updateIntefaceData(long time_atual){ // quando é chamada atualizar a inteface remota com os dados coletados
  if(time_atual-aux_cont_update>400){
    notifyClients("EMP="+String((-0.0002264*empuxo) + 1877.7218));
    notifyClients("CARG_CAP="+String(cap_carga));
    notifyClients("BAT="+String(bateria));
    aux_cont_update=time_atual;
  }   
}
void layotIgnicao(int type){ // quando é chamada adequa o display para exibir (conatgem, cancelamento e carga insuficiente )
  if(type==1){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("EQUIPE PRD");
    lcd.setCursor(0, 1);
    lcd.print("Contagem regressiva"); 
  }else if(type==2){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("EQUIPE PRD");
    lcd.setCursor(0, 1);
    lcd.print("Cancelada!!");
  }else{
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("EQUIPE PRD");
    lcd.setCursor(0, 1);
    lcd.print("Carga insuficiente!");
  }
}
