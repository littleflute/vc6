// file: blclass.js
// by littleflute
// 2017/11/3 23:55am bjt


var blColor	= ["red","tomato","gold","black","green","blue","lightblue","yellow","brown","pink","gray","white","mediumpurple",
	"cyan"];
var blGrey	= ["Gainsboro","LightGray","Silver","DarkGray",
			   "DimGray","Gray","LightSlateGray","SlateGray","DarkSlateGray","black"];

	function _on_off_div(b,d){//v1037	 xdvc6	
		if(d.style.display=="block"){
			d.style.display="none"; 
			b.style.backgroundColor="red"; 
		}
		else{
			d.style.display="block";
			b.style.backgroundColor="green"; 
		}
	};
	function _on_off_bd_1(b,d){ //v1036	 xdvc6	
		if(b.bOnOff){
			b.bOnOff = false;
			b.style.backgroundColor="green"; 
		}
		else{
			b.bOnOff = true;
			b.style.backgroundColor="red"; 
		}
		if(d.style.display=="block"){
			d.style.display="none"; 
		}
		else{
			d.style.display="block";
		}
	}
	function _on_off_bd(b,d){ //v1035	 xdvc6	
		if(b.innerHTML=="+"){
			b.innerHTML = "-";
			b.style.backgroundColor="green"; 
		}
		else{
			b.innerHTML = "+";
			b.style.backgroundColor="red"; 
		}
		if(d.style.display=="block"){
			d.style.display="none"; 
		}
		else{
			d.style.display="block";
		}
	}
	function _getXY(){
			
			var scrlY =document.body.scrollTop;
			var scrlX =document.body.scrollLeft;
			var r = {};
			r.x=event.clientX+scrlX;
			r.y=event.clientY+scrlY; 
			return r;
	}
function xdMoveDivClass(idDiv)
{	
	var _id			= idDiv;
	var divShowMe	= blo0.blMDiv(document.body,_id,"divShowMe: xdMoveDivClass",350,150,500,200,blColor[1]);
	var m2			= blo0.blMDiv(document.body,"MMMM","mmmm",50,350,200,200,blColor[4]);
	var dm = null;
	var x1 = 0;
	var y1 = 0;
	var _v = "xdMoveDivClass: v0.0.27";
	
	this.bll0		= "-xdMoveDivClass-";
	this.blrMove = _moveDivHandleFun;
	this.blrM2Test = function(b,v){ 
		blo0.blDiv(m2,"m222","m2222");
	} 
	this.bll1		= "-----";
	
	this.blhShow = function(){ 
		this.d.innerHTML = _v + _blRect(_v,this.x,this.y,this.w,this.h,this.c);
	}

	this.x = 0;
	this.y = 0;
	this.w = 0;
	this.h = 0;
	this.c = "blue";
	this.d = null;
	function _getXY(){			
			var scrlY =document.body.scrollTop;
			var scrlX =document.body.scrollLeft;
			var r = {};
			r.x=event.clientX+scrlX;
			r.y=event.clientY+scrlY; 
			return r;
	}
	function _blRect (txt,x,y,w,h,color){
		var s = '<div style="position:absolute;left:'+x+';top:'+y+';';
		s += 'width:' + w + ';';
		s += 'height:' + h + ';';
		s += 'background-color:' + color + ';';
		s += '">';
		s += txt;
		s += '[';
		s += x + "," + y + "]";
		s += '</div>'; 
		return s;
	}
	this.blhInitUI		= function(divUI){
		var dUI = blo0.blDiv(divUI,divUI.id + "_initUI_xdMoveDivClass" + _v,_v,"green");
		var b1 = blo0.blBtn(dUI,dUI.id + "b1","[xdMoveDivClass]",blColor[8]);
		b1.onclick= function(this_){
			return function(){
				var d = document.getElementById(_id);
				blo0.blShowObj2Div(d,this_);
			}
		}(this);
	};
	function _moveDivHandleFun(b,v){ 
		if(v.style.display=="block"){
			v.style.display="none"; 
		}
		else{
			v.style.display="block";
		}
		var l = v.parentNode.style.left;
		l = parseInt(l); 
		v.innerHTML = l; 
		dm = blo0.blDiv(v,"blMoveMark","moveMark");
		dm.style.cursor = "move";

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
			if(x1==0 && y1==0) return false;

			var l = v.parentNode.style.left;

			l = parseInt(l);
			v.parentNode.style.left = l + c.x -x1 + "px";
			var t = v.parentNode.style.top;
			t = parseInt(t);
			v.parentNode.style.top = t + c.y -y1 + "px";
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
	}
}//xdMoveDivClass
function blClass ()
{ 
	var _id = "id_div_4_blClass";
    this.v = "xdvc6: 1.0.51";//blclassdbg

    this.blrTest = function (b,d)
    {        
		 d.parentElement.parentElement.style.display = "none";
	}
	this.blhInitUI		= function(divUI){	
		var divMove		= blo0.blMDiv(document.body,_id,"divShowMe_divMove_blClass",550,150,500,200,blColor[8]);
		var divShowMe	= blo0.blDiv(divMove,divMove.id + "ShowMe","divShowMe",blColor[6]);
		var dUI = blo0.blDiv(divUI,divUI.id + "_initUI_blClass" + this.v,this.v,"green");
		var b1 = blo0.blBtn(dUI,dUI.id + "b1","[blClass]",blColor[8]);
		b1.onclick= function(this_){
			return function(){ 
				blo0.blShowObj2Div(divShowMe,this_);
				divMove.style.display = "block";
			}
		}(this);
	};
    this.blCreatePage = function (titleTxt,bodyHtml){
		var r = "";
		r	+= "<HTML><HEAD><TITLE>";
		r	+= titleTxt;
		r	+= "</TITLE></HEAD>";
		r	+= "<body>";
		r	+= bodyHtml;
		r	+= "</body></HTML>";

		return r;
	};
    this.blMDiv = function (oBoss,id,html,x,y,w,h,bkClr){
		var x1 = 0;
		var y1 = 0;
		var t	= this.blDiv(oBoss,id+"_blClass_blMDiv",html,bkClr?bkClr:"gold");
        var r = document.getElementById(id);
        if(!r){
            r = document.createElement("div");
            r.id = id;
    	    r.innerHTML = html; 
            r.style.backgroundColor=bkClr?bkClr:"gold";
			r.style.position = "absolute";
			r.style.left		= x+"px";
			r.style.top			= y+"px";
			r.style.width		= w+"px";
			r.style.height		= h+"px";
			r.style.cursor		= "default";
    	    if(t!=null)t.appendChild(r);
		}	
		var mbody	= this.blDiv(r,id+"mbody","mbody","skyblue");
		mbody.style.cursor		= "move";
		var main	= this.blDiv(r,id+"main","main","green");
		var dm = r;
		mbody.onmousedown = function(){
			var c = _getXY();
			main.innerHTML = "down:" + c.x + "," + c.y;
			x1 = c.x;
			y1 = c.y;
			return false;
		};
		mbody.onmousemove = function(){
			var c = _getXY();
			main.innerHTML = "move:" + c.x + "," + c.y; 
			if(x1==0 &&y1==0) return false;

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
		mbody.onmouseup = function(){
			var c = _getXY();
			main.innerHTML = "up:" + c.x + "," + c.y; 
			x1 = 0;
			y1 = 0; 
		}; 
		mbody.onmouseout = function(){
			var c = _getXY();
			main.innerHTML = "out:" + c.x + "," + c.y; 
			x1 = 0;
			y1 = 0; 
		};  
        return r;
    }
    _blShowObj2Div_all = function (oBoss,obj,l) //blclassdbg 1039
    {	  
        oBoss.innerHTML = "";
        for(i in obj)
		{
			var bOK = i.charAt(0)=="b"&&i.charAt(1)=="l"&&i.charAt(2)=="r"; 
			if(!bOK) continue;

			  var b = document.createElement("button");
			  b.id = b.innerHTML = i;
			  var color = "gray";
			  if(1==l) color = "blue";
			  else if( 2==l) color = "pink";
			  else if( 3==l) color = "red";

			  b.style.backgroundColor = color;
			  if(i.charAt(0)=="b"&&i.charAt(1)=="l") b.style.backgroundColor = "yellow";
			  oBoss.appendChild(b);
			  var d = document.createElement("div");
			  if("object" == typeof obj[i])
			  {
					_blShowObj2Div_all(d,obj[i],l+1);
			  }
			  else{
				d.innerHTML = obj[i];
			  }
			  d.style.border = "blue 1px solid";
			  d.style.backgroundColor = "green";
			  d.style.color = "yellow";
			  oBoss.appendChild(d);

			  
			  if(bOK){
				b.style.backgroundColor = "red";
				d.innerHTML = ""; 
				d.id = b.id + "Div";
				b.onclick = function(i_,b_,v_,o_){
					return function(){
						var go = obj[i_];
						if (typeof go == "function") {
			    			go(b_,v_,o_);
						}
					} 
				}(i,b,d,obj);
			  }
		}		 
	}
    this.blShowObj2Div_all = function (oBoss,obj,l) //blclassdbg 1039
    {	 
        _blShowObj2Div_all(oBoss,obj,l);	 
	}
    this.blShowObj2Div = function (oDivBoss,obj)
    {	 
		_blShowObj2Div(oDivBoss,obj);
		 
	}
    _blShowObj2Div = function (oDivBoss,obj)
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
			  if(i.charAt(0)=="b"&&i.charAt(1)=="l"&&i.charAt(2)=="l"){ 
					b.style.display = "none";	//v1033	 xdvc6
					d.id			= d.html;	 
			  }
			  if(i.charAt(0)=="b"&&i.charAt(1)=="l"&&i.charAt(2)=="h"){ 
					b.style.display = "none";	//v1034	 xdvc6	
					d.style.display = "none";	//v1034	 xdvc6	
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