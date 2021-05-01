void iniciar_ignicao(bool op, char* data){ // quando é chamada altera o status de ignição e sinalisa ao usuario 
  if(cap_carga>=90){
    if(op){
      contagem=true;
      notifyClients(String(data));
      layotIgnicao(1);
    }else{
       time_cont=10;
       contagem=false;
       notifyClients(String(data));
       layotIgnicao(2);
    }
  }else{ // caso a carga dos capacitores for inferior a 90%, informa ao usuario que não é possivel ignitar 
    notifyClients("ERRO=Carga insuficiente");
    layotIgnicao(3);
  } 
}
void iniciar_carga(bool op, char* data){// quando é chamada altera o status de carregamento dos cap e sinalisa ao usuario 
  if(op){
    carga=true;
    notifyClients(String(data));
  }else{
    carga=false;
    notifyClients(String(data));
  }
}
void iniciar_descarga(bool op, char* data){// quando é chamada altera o status de descarregamento dos cap e sinalisa ao usuario 
  if(op){
    descarga=true;
    notifyClients(String(data));
  }else{
    descarga=false;
    notifyClients(String(data));
  }
}

// funções usadas durante a interrupçao (usuario manual)
ICACHE_RAM_ATTR void attach_ig(){// quando o bottão é pressionado essa função é chamada e chama a iniciar_ignicao
  if(contagem==true){
    iniciar_ignicao(false, "IG=0");
  }else{
    iniciar_ignicao(true, "IG=1");
  }
 while(digitalRead(pin_bottao_ig)==0);
}
ICACHE_RAM_ATTR void attach_carga(){ // quando o bottão é pressionado essa função é chamada e chama a iniciar_carga
  if(digitalRead(pin_bottao_carga)==1){
    iniciar_carga(false, "CARG=0");
  }else{
    iniciar_carga(true, "CARG=1");
  }
}
