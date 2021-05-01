const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>System Launch PRD</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="utf-8">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 21px;
    color: white;
    font-family: -webkit-pictograph;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color:rgb(14, 14, 14);
    height: 55px;
  }
  body {
    margin: 0;
    background-color:rgb(14, 14, 14);
  }
  .content {
    max-width: 600px;
    margin: 0 auto;
  }
  .button {
    margin-top: 10px;
    width: 48%;
    height: 49px;
    font-size: 15px;
    outline: none;
    border: none;
    border-radius: 5px;
  }
  .bk_red{
    background: darkred;
    color: antiquewhite;
  }
  .bk_green{
    background:darkgreen;
    color: antiquewhite;
  }
  .bk_orange{
    background:darkorange;
    color: antiquewhite;
  }
  .bk_blue{
    background: rgb(61, 122, 163);
    color:white;
  }
  .text_display{
    color: white;
    text-align: left;
    font-size: 19px;
    margin:7px;
    font-family: system-ui;
  }
  .text_display_cont{
    color: white;
    font-size: 20px;
    margin:7px;
    margin-top: -5px;
    font-family: system-ui;
  }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
      opacity: 0.4;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .display_{ 
    background: black;
    padding: 5px;
   }
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>System Launch PRD</h1>
  </div>
  <div class="content">
    <div style="width: 85%;margin-left: 5%;background:#2b2a2fa6;padding: 3%;margin-top: 20px;margin-bottom: 30px;border-radius: 5px;">
      <div style="text-align: center;width: 100%;background: midnightblue;padding: 1px;margin-top: -20px;margin-bottom: 10px;font-size: 20px;color:whitesmoke">Console</div>
      <div id = "list" style="padding: 10px;background: black;min-height: 85px;">
        <p class="text_display">Capacitores: <i id="cap_carga">0</i></p>
         <p class="text_display"> Status: <i id="status" style="color: yellow;">Em espera</i></p>
         <p class="text_display">Empuxo: <i id="empuxo" >0</i></p>
         <p class="text_display">Bateria: <i id="bateria">0</i></p>
         <hr>
         <p class="text_display_cont">Contagem regressiva:</p>
         <p class="text_display_cont" style="font-size: 26px;" id="cont_reg">00</p>
      </div>
    </div>
    <div style="padding: 3%;width: 85%;margin-left: 5%;background:#2b2a2fa6;margin-top: 15px;margin-bottom: 30px;border-radius: 5px;">
      <div style="text-align: center;width: 100%;background: midnightblue;padding: 1px;margin-top: -20px;font-size: 20px;color:whitesmoke">Controles</div>
      <button id="b_ig" class="button bk_green">IGNITAR</button>
      <button id="b_ig_stop" class="button bk_red" style="display:none">ABORTAR</button>
      
      <button id="b_carg" class="button">LIG CARGA</button>
      <button id="b_carg_stop" class="button" style="display:none">DESL CARGA</button>
      
      <button id="b_dcarg" class="button bk_orange">LIG DESCARGA</button>
      <button id="b_dcarg_stop" class="button bk_orange" style="display:none">DESL DESCARGA</button>
      <button id="b_test" class="button bk_blue">CONEXÃO</button>
      
    </div> 
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  var time_test_CNX=0;
  var cont;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }

  function onMessage(event) {
    var option; 
    if (event.data == "IG=-1"){
      document.getElementById('status').innerHTML = "Ignição";
      document.getElementById('b_ig_stop').setAttribute('style','display:none');
      document.getElementById('b_ig').removeAttribute('style');
    }else if (event.data == "IG=1"){
      document.getElementById('status').innerHTML = "Contagem Regressiva"; 
      document.getElementById('b_ig').setAttribute('style','display:none');
      document.getElementById('b_ig_stop').removeAttribute('style');
    }else if(event.data == "IG=0"){
      document.getElementById('status').innerHTML = "Ignição Interrompida";
      document.getElementById('b_ig_stop').setAttribute('style','display:none');
      document.getElementById('b_ig').removeAttribute('style');
    }else if(event.data == "CARG=0"){
      document.getElementById('status').innerHTML = "Carga Desligada";
      document.getElementById('b_carg_stop').setAttribute('style','display:none');
      document.getElementById('b_carg').removeAttribute('style');
    }else if(event.data == "CARG=1"){
      document.getElementById('status').innerHTML ="Carga Ligada";
      document.getElementById('b_carg').setAttribute('style','display:none');
      document.getElementById('b_carg_stop').removeAttribute('style');
    }else if(event.data == "DES=0"){
      document.getElementById('status').innerHTML ="Descarga Desligada";
      document.getElementById('b_dcarg_stop').setAttribute('style','display:none');
      document.getElementById('b_dcarg').removeAttribute('style');
    }else if(event.data == "DES=1"){
      document.getElementById('status').innerHTML ="Descarga Ligada";
      document.getElementById('b_dcarg').setAttribute('style','display:none');
      document.getElementById('b_dcarg_stop').removeAttribute('style');
    }else if(event.data.indexOf("CONT_IG") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
        document.getElementById('cont_reg').innerHTML = option;
        document.getElementById('status').innerHTML = "Contagem Regressiva";
    }else if(event.data.indexOf("CARG_CAP") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
         if(parseInt(option)>=90){
          document.getElementById('cap_carga').innerHTML = option+"% - OK";
          document.getElementById('cap_carga').setAttribute('Style','color:green');
        }else{
          document.getElementById('cap_carga').innerHTML = option+"%";
          document.getElementById('cap_carga').setAttribute('Style','color:red');
        } 
    }else if(event.data.indexOf("BAT") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
        if(parseInt(option)>=50){
          document.getElementById('bateria').innerHTML = option+"% - Boa";
          document.getElementById('bateria').setAttribute('Style','color:green');
        }else if(parseInt(option)>=20){
          document.getElementById('bateria').innerHTML = option+"% - Atenção";
          document.getElementById('bateria').setAttribute('Style','color:yellow');
        }else{
          document.getElementById('bateria').innerHTML = option+"% - Carregue!";
          document.getElementById('bateria').setAttribute('Style','color:red');
        }
    }else if(event.data.indexOf("EMP") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
        document.getElementById('empuxo').innerHTML = option;
    }else if(event.data.indexOf("ERRO") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
        document.getElementById('status').innerHTML = option;
    }else if(event.data.indexOf("CNX") != -1){
        clearInterval(cont);
        if(time_test_CNX==0){
        }else if(time_test_CNX<=0.5){
            document.getElementById('status').innerHTML = "Conexão Boa";
        }else if(time_test_CNX<=1){
            document.getElementById('status').innerHTML = "Conexão meio Lenta";
        }else{
          document.getElementById('status').innerHTML = "Conexão  Lenta";
        }
        time_test_CNX=0;
    }
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function cont_CNX() {
    time_test_CNX+=0.05;
    cont = setInterval(ver_cnx, 50);
  }
  function ver_cnx(){
    time_test_CNX+=0.05;
    if(time_test_CNX>=2.0){
        clearInterval(cont);
        document.getElementById('status').innerHTML = "Falha na conexão";
        time_test_CNX=0;
    }
  }
  function initButton() {
    document.getElementById('b_ig').addEventListener('click', ignitar);
    document.getElementById('b_ig_stop').addEventListener('click', stop_ig);
    document.getElementById('b_carg').addEventListener('click', carregar);
    document.getElementById('b_carg_stop').addEventListener('click', stop_carg);
    document.getElementById('b_dcarg').addEventListener('click', descarregar);
    document.getElementById('b_dcarg_stop').addEventListener('click', stop_dcarg);
    document.getElementById('b_test').addEventListener('click', test);
  }
  function ignitar(){
    websocket.send('IG=1');
  }
  function stop_ig(){
    websocket.send('IG=0');
  }
  function carregar(){
    websocket.send('CARG=1');
  }
  function stop_carg(){
    websocket.send('CARG=0');
  }
  function descarregar(){
    websocket.send('DES=1');
  }
  function stop_dcarg(){
    websocket.send('DES=0');
  }
  function test(){
    websocket.send('CNX');
    cont_CNX();
  }
</script>
</body>
</html>
)rawliteral";