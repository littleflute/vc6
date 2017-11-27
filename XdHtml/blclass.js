// file: blclass.js
// by littleflute
// 2017/11/3 23:55am bjt

	function _getXY(){
			
			var scrlY =document.body.scrollTop;
			var scrlX =document.body.scrollLeft;
			var r = {};
			r.x=event.clientX+scrlX;
			r.y=event.clientY+scrlY; 
			return r;
	}
function blClass ()
{ 
    this.v = "vc: 1.0.23";

    this.blrTest = function ()
    {        
		alert("blrTest");
	}
    this.blMDiv = function (oBoss,id,html,bkClr){
		var x1 = 0;
		var y1 = 0;
        var r = document.getElementById(id);
        if(!r){
            r = document.createElement("div");
            r.id = id;
    	    r.innerHTML = html; 
            r.style.backgroundColor=bkClr?bkClr:"gold";
			r.style.position = "absolute";
			r.style.width		= 200+"px";
			r.style.top			= 200+"px";
			r.style.left		= 200+"px";
			r.style.cursor		= "move";
    	    if(oBoss!=null)oBoss.appendChild(r);
        }
		var dm = r;
		dm.onmousedown = function(){
			var c = _getXY();
			dm.innerHTML = "down:" + c.x + "," + c.y;
			x1 = c.x;
			y1 = c.y;
			return false;
		};
		dm.onmousemove = function(){
			var c = _getXY();
			dm.innerHTML = "move:" + c.x + "," + c.y; 
			if(x1==0) return false;

			var l = dm.style.left;
			l = parseInt(l);
			dm.style.left = l + c.x -x1 + "px";

			var t = dm.style.top;
			t = parseInt(t);
			dm.style.top = t + c.y -y1 + "px";
			
			x1 = c.x;
			y1 = c.y;
			return false;
		};
		dm.onmouseup = function(){
			var c = _getXY();
			dm.innerHTML = "up:" + c.x + "," + c.y; 
			x1 = 0;
			y1 = 0; 
		}; 
		dm.onmouseout = function(){
			var c = _getXY();
			dm.innerHTML = "out:" + c.x + "," + c.y; 
			x1 = 0;
			y1 = 0; 
		}; 
        return r;
    }
    this.blShowObj2Div = function (oDivBoss,obj)
    {        
        var oBoss = oDivBoss;
        if(!oBoss) {
           oBoss = document.createElement("div");
           oBoss.id = "divBlShowObj";
           oBoss.style.border = "green 1px solid";
           document.body.appendChild(oBoss);
        } 
        if(!oBoss){
            alert("boss error!");return;
        }
        oBoss.innerHTML = "";
        for(i in obj)
        {
          var b = document.createElement("button");
          b.id = b.innerHTML = i;
		  b.style.backgroundColor = "gray";
          if(i.charAt(0)=="b"&&i.charAt(1)=="l") b.style.backgroundColor = "yellow";
          oBoss.appendChild(b);
          var d = document.createElement("div");
          d.innerHTML = obj[i];
          d.style.border = "blue 1px solid";
          d.style.backgroundColor = "green";
          d.style.color = "yellow";
          oBoss.appendChild(d);

          if(i.charAt(0)=="b"&&i.charAt(1)=="l"&&i.charAt(2)=="r"){
			b.style.backgroundColor = "red";
			d.innerHTML = ""; 
			d.id = b.id + "Div";
			b.onclick = function(i_,b_,v_){
				return function(){
					var go = obj[i_];
					if (typeof go == "function") {
			    		go(b_,v_);
					}
			} 
		}(i,b,d);
	  }
        }
    }    

	this.blAudio = function (oBoss,id,src)					
 	{  								
   		var s = "";							 
	   	s += "<";						 
	   	s += "audio id=";						
   		s += id;							
	   	s += " controls>";								 
	   	s += "<source src='";
		s += src;
		s += "' type='audio/mpeg'>";		 
		s += "Your browser does not supoort hte audio element"				
	   	s += "</audio>";								 
	   	oBoss.innerHTML = s;						 
	 }	

	this.blScript = function (id,src){
    		var r = document.getElementById(id);
    		if(!r){
        		r = document.createElement("script");
        		r.id = id;
    		}
    		r.src = src; 
    		document.body.appendChild(r);
    		return r;
	}

    this.blAjx = function(worker,href)
    {
        var xmlhttp;
        if (window.XMLHttpRequest)
        {// code for IE7+, Firefox, Chrome, Opera, Safari
            xmlhttp=new XMLHttpRequest();
        }
        else
        {// code for IE6, IE5
            xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange=function()
        {
            if (xmlhttp.readyState==4 && xmlhttp.status==200)
            {
               worker._2do(xmlhttp.responseText);
            }
        }
        xmlhttp.open("GET",href,true);
        xmlhttp.send();
    }

    this.blDiv = function (oBoss,id,html,bkClr){
        var r = document.getElementById(id);
        if(!r){
            r = document.createElement("div");
            r.id = id;
    	    r.innerHTML = html; 
            r.style.backgroundColor=bkClr?bkClr:"gray";
    	    if(oBoss!=null)oBoss.appendChild(r);
        }
        return r;
    }
    this.blTextarea = function (oBoss,id,html,bkClr){
        var r = document.getElementById(id);
        if(!r){
            r = document.createElement("Textarea");
            r.id = id;
    	    r.innerHTML = html; 
            r.style.backgroundColor=bkClr?bkClr:"gray";
    	    if(oBoss!=null)oBoss.appendChild(r);
        }
        return r;
    }

    this.blBtn = function (oBoss,id,html,bkClr){
        var r = document.getElementById(id);
        if(!r){
            r = document.createElement("button");
            r.id = id;
    	    r.innerHTML = html; 
            r.style.backgroundColor=bkClr?bkClr:"green";
    	    if(oBoss!=null)oBoss.appendChild(r);
        }
        return r;
    }
    this.blLink = function (oBoss,id,html,href,bkClr){
        var r = document.getElementById(id);
        if(!r){
            r = document.createElement("a");
    	    var t = document.createTextNode(html);
    	    r.setAttribute("href", href);
            r.id = id; 
    	    r.style.backgroundColor = bkClr?bkClr:"blue";
        }
        r.innerHTML = html + " "; 
        oBoss.appendChild(r);
        return r;
    }

    this.blMakeDivMovable = function (elmnt) {
      	var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
	var idHeader = document.getElementById(elmnt.id + "Header");
      	if (idHeader) {
        	/* if present, the header is where you move the DIV from:*/
        	idHeader.onmousedown = dragMouseDown;
      	} else {
        	/* otherwise, move the DIV from anywhere inside the DIV:*/
        	elmnt.onmousedown = dragMouseDown;
      	}

      	function dragMouseDown(e) {
        	e = e || window.event;
        	// get the mouse cursor position at startup:
        	pos3 = e.clientX;
        	pos4 = e.clientY;
        	document.onmouseup = closeDragElement;
        	// call a function whenever the cursor moves:
        	document.onmousemove = elementDrag;
		if (idHeader) {
        		idHeader.innerHTML = pos3 + "," + pos4;
      		}	
      	}

      function elementDrag(e) {
        e = e || window.event;
        // calculate the new cursor position:
        pos1 = pos3 - e.clientX;
        pos2 = pos4 - e.clientY;
        pos3 = e.clientX;
        pos4 = e.clientY;
        // set the element's new position:
        elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
        elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
      }

      function closeDragElement() {
        /* stop moving when mouse button is released:*/
        document.onmouseup = null;
        document.onmousemove = null;
      }
    }
	
}//END: function blClass ()
 
 var blo0 = new blClass;