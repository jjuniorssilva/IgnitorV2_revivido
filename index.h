const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="utf-8"
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
    background-color:darkgray;
  }
  .content {
    max-width: 600px;
    margin: 0 auto;
  }
  .button {
    width: 90%;
    height: 50px;
    font-size: 20px;
    outline: none;
    border: solid 1px black;
   }
  .text_display{
    color: white;
    text-align: left;
    font-size: 19px;
    margin:7px;
  }
  .text_display_cont{
    color: white;
    font-size: 20px;
    margin:7px;
    margin-top: -5px;
  }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
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
    
      <div class="display_">
         <p class="text_display">Capacitores: <i id="cap_carga" style="color: red;">0</i>%</p>
         <p class="text_display"> Status: <i id="status" style="color: yellow;">Em espera</i></p>
         <p class="text_display">Empuxo: <i id="empuxo" style="color:brown">0</i></p>
         <p class="text_display">Bateria: <i id="bateria" style="color:brown">0</i></p>
         <hr>
         <p class="text_display_cont">Contagem regressiva:</p>
         <p class="text_display_cont" style="font-size: 26px;" id="cont_reg">00</p>
      </div>
      <p><button id="b_ig" class="button">Ignitar</button></p>
      <p><button id="b_ig_stop" class="button" style="display:none">Interomper</button></p>
      
      <p><button id="b_carg" class="button">Carga</button></p>
      <p><button id="b_carg_stop" class="button" style="display:none">Parar Carga</button></p>
      
      <p><button id="b_dcarg" class="button">Descarga</button></p>
      <p><button id="b_dcarg_stop" class="button" style="display:none">Parar Descarga</button></p>

  
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
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
      document.getElementById('status').innerHTML = "Contagem Regressiva"; // corrigir
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
        document.getElementById('cap_carga').innerHTML = option; 
    }else if(event.data.indexOf("BAT") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
        document.getElementById('bateria').innerHTML = option;
    }else if(event.data.indexOf("EMP") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
        document.getElementById('empuxo').innerHTML = option;
    }else if(event.data.indexOf("ERRO") != -1){
        option = event.data.substring(event.data.indexOf("=")+1);
        document.getElementById('status').innerHTML = option;
    }
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('b_ig').addEventListener('click', ignitar);
    document.getElementById('b_ig_stop').addEventListener('click', stop_ig);
    document.getElementById('b_carg').addEventListener('click', carregar);
    document.getElementById('b_carg_stop').addEventListener('click', stop_carg);
    document.getElementById('b_dcarg').addEventListener('click', descarregar);
    document.getElementById('b_dcarg_stop').addEventListener('click', stop_dcarg);
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
</script>
</body>
</html>
)rawliteral";