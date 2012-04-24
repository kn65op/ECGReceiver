<script language="JavaScrip" type="text/javascript">                 
   var ws = new WebSocket("ws://localhost:8888/");   
   ws.onopen = function() {   
    console.log('connected');  
    ws.send("start");
     };   
  
  ws.onerror = function(evt) { alert(evt) };
     ws.onmessage = function (e) { alert(e.data); ws.send("0"); };   
     ws.onclose = function() { console.log('closed'); };  
</script>

