var f2 = function(b,d){
	//f2.js music staff
  var _v			= "v0.0.511";  

  var _ui = new _UIClass;
  function _noteClass(o){
	var i = o.notes.length + 1;
	var x = i*33, y = 100, w=22, h=100,c=6,d="8",t="1",xn=90,yn=60;	

	var divID = o.id + "_div_beat" + i;     
	var s0 = "<div id='" + divID + "_t" + "'>f</div>";

	var divNote = blo0.blMDiv(o,divID,s0,x,y,w,h,"gray");   
	divNote.tbWrap = bl$(divID + "_t"); divNote.tbWrap.innerHTML = "tbWrap";  
	divNote.tbWrap.b1 = blo0.blBtn(divNote.tbWrap,divNote.tbWrap.id+"b1","b1",blGrey[1]);  
	divNote.tb = blo0.blDiv(divNote.tbWrap,divNote.tbWrap.id+"tb","tb",blGrey[0]); 
	divNote.tbWrap.b1.onclick  = function(_d){return function(){_on_off_div(this,_d)}}(divNote.tb);

	divNote.followDiv = blo0.blMDiv(o,divID+"_follow","",x,y+122,1,h,"red"); 
	divNote.jgo		= new _jgClass(divNote.followDiv,0,55,1,22,blGrey[3]);  

	divNote.Num = i; 
	divNote.followDiv.blhShowMe = function(jg){ 
		jg.setColor(blColor[4]); 
		jg.fillRect(20,55,33,22);
		jg.setColor(blColor[5]);  
		this._draw_note_as_music(xn,yn);
	}
	divNote.followDiv._draw_note_as_music = function (x0,y0){
		var v = "v25";
		var x = x0;
		var y = y0; 
		var r = divNote.jgo.draw_music_c(c,x,y);
		x = r.x;
		y = r.y; 
		var r = divNote.jgo.draw_music_d(d,x,y);
		x = r.x;
		y = r.y; 
		divNote.jgo.draw_music_t(t,d,x0,y0,x,y); 
	}
	 
	divNote.tb.xn1 = blo0.blBtn(divNote.tb,divNote.tb.id+"xn1","xn+",blGrey[0]);
	divNote.tb.xn2 = blo0.blBtn(divNote.tb,divNote.tb.id+"xn2","xn-",blGrey[0]);
	divNote.tb.b1 = blo0.blBtn(divNote.tb,divNote.tb.id+"b1","b1",blGrey[0]);
	divNote.tb.b2 = blo0.blBtn(divNote.tb,divNote.tb.id+"b2","b2",blGrey[0]);
	divNote.tb.b3 = blo0.blBtn(divNote.tb,divNote.tb.id+"b3","c+",blGrey[0]);
	divNote.tb.b4 = blo0.blBtn(divNote.tb,divNote.tb.id+"b4","c-",blGrey[0]);
	divNote.tb.b5 = blo0.blBtn(divNote.tb,divNote.tb.id+"b5","t=1",blGrey[0]);
	divNote.tb.b6 = blo0.blBtn(divNote.tb,divNote.tb.id+"b6","t=-1",blGrey[0]);
	divNote.tb.b7 = blo0.blBtn(divNote.tb,divNote.tb.id+"b7","16b",blGrey[0]);
	divNote.tb.b8 = blo0.blBtn(divNote.tb,divNote.tb.id+"b8","16e",blGrey[0]);
	divNote.tb.b9 = blo0.blBtn(divNote.tb,divNote.tb.id+"b9","16=",blGrey[0]);
	divNote.tb.b10 = blo0.blBtn(divNote.tb,divNote.tb.id+"b10","16-",blGrey[0]);
	divNote.tb.b11 = blo0.blBtn(divNote.tb,divNote.tb.id+"b11","16",blGrey[0]);
	divNote.tb.b12 = blo0.blBtn(divNote.tb,divNote.tb.id+"b12","8b",blGrey[0]);
	divNote.tb.b13 = blo0.blBtn(divNote.tb,divNote.tb.id+"b13","8e",blGrey[0]);
	divNote.tb.b14 = blo0.blBtn(divNote.tb,divNote.tb.id+"b14","8",blGrey[0]);
	divNote.tb.xn1.onclick = function(_d){	return function(){ xn++;_d.jgo.update();}}(divNote); 
	divNote.tb.xn2.onclick = function(_d){	return function(){ xn--;_d.jgo.update();}}(divNote); 
	divNote.tb.b1.onclick = function(_d){	return function(){ _on_off_div(this,_d.handle);_on_off_div(this,_d.main);}}(divNote.followDiv);
	divNote.tb.b2.onclick = function(_d){	return function(){ _d.jgo.set(0,50,30,20);}}(divNote); 
	divNote.tb.b3.onclick = function(_d){	return function(){ c++;_d.jgo.update();}}(divNote);  
	divNote.tb.b4.onclick = function(_d){	return function(){ c--;_d.jgo.update();}}(divNote);  
	divNote.tb.b5.onclick = function(_d){	return function(){ t="1";;_d.jgo.update();}}(divNote);  
	divNote.tb.b6.onclick = function(_d){	return function(){ t="-1";_d.jgo.update();}}(divNote);  
	divNote.tb.b7.onclick = function(_d){	return function(){ d="16b";_d.jgo.update();}}(divNote);  
	divNote.tb.b8.onclick = function(_d){	return function(){ d="16e";_d.jgo.update();}}(divNote); 
	divNote.tb.b9.onclick = function(_d){	return function(){ d="16=";_d.jgo.update();}}(divNote);  
	divNote.tb.b10.onclick = function(_d){	return function(){ d="16-";_d.jgo.update();}}(divNote); 
	divNote.tb.b11.onclick = function(_d){	return function(){ d="16";_d.jgo.update();}}(divNote); 
	divNote.tb.b12.onclick = function(_d){	return function(){ d="8b";_d.jgo.update();}}(divNote); 
	divNote.tb.b13.onclick = function(_d){	return function(){ d="8e";_d.jgo.update();}}(divNote); 
	divNote.tb.b14.onclick = function(_d){	return function(){ d="8";_d.jgo.update();}}(divNote); 
	divNote.jgo.update();
	divNote.tb.b1.onclick();		divNote.tb.b1.onclick();
	divNote.tbWrap.b1.onclick();	divNote.tbWrap.b1.onclick();
  }
  function _jgClass(oDiv,x1,y1,w1,h1,c1){
  	var _view = blo0.blDiv(oDiv,oDiv.id+"divView","",blGrey[0]);
	var _jg = new jsGraphics(_view.id);
	var x=x1,y=y1,w=w1,h=h1,c=c1,o=oDiv;
	function _drawAll(){
		_jg.clear();
		_jg.setColor(c);
		_jg.fillRect(x,y,w,h); 
		if(o.blhShowMe){o.blhShowMe(_jg);}
		_jg.paint();
	}   
	this.update	= function()			{ _drawAll(); }   
	this.set	= function(x1,y1,w1,h1) { x=x1;y=y1;w=w1;h=h1; _drawAll(); }   
	this.draw_music_c	= function (c,x0,y0){ 
		_jg.drawString(c,x0,y0); 
		var r = {};
		r.x = x0;
		r.y = y0 + 15;
		return r;
	}
	this.draw_music_d	= function (d,x0,y0){
		var jg = _jg;
		var x = x0;
		var y = y0; 
		if(d){
			var dx = 10;
			var dy = 2;
			var x1 = x;
			var x2 = x+dx;  
			switch(d)
			{
			case "16b":
				x2 += dx;
				jg.drawLine(x1,y,x2,y);
				y += dy;
				jg.drawLine(x1,y,x2,y); 
				break;
			case "16e":
				x1 -= dx;
				jg.drawLine(x1,y,x2,y);
				y += dy;
				jg.drawLine(x1,y,x2,y); 
				break;
			case "16=":
				x1 -= dx;
				x2 += dx;
				jg.drawLine(x1,y,x2,y);
				y += dy;
				jg.drawLine(x1,y,x2,y); 
				break;
			case "16-":
				x1 -= dx;
				x2 += dx;
				jg.drawLine(x1,y,x2,y);
				x1 += dx;
				y += dy;
				jg.drawLine(x1,y,x2,y); 
				break;
			case "16": 
				jg.drawLine(x1,y,x2,y);
				y += dy;
				jg.drawLine(x1,y,x2,y); 
				break;
			case "8":
				jg.drawLine(x1,y,x2,y); 
				break;
			case "8b":
				x2 += dx;
				jg.drawLine(x1,y,x2,y); 
				break;
			case "8e":
				x1 -= dx;
				jg.drawLine(x1,y,x2,y); 
				break;
			} 
		}  
		var r = {};
		r.x = x;
		r.y = y;
		return r;
	}
	this.draw_music_t	= function (t,d,x0,y0,x,y){
		var jg = _jg;
		var x_ = x;
		var y_ = y;  
		if(t){ 
			switch(t)
			{
			case "-1":
				if(d=="8"||d=="8b"||d=="8e")			y_ += 3;
				else if(d=="16"||d=="16b"||d=="16e")	y_ += 2*3; 

				x_ = x0 + 3;
				jg.fillEllipse(x_,y_,2,2); 
				break;
			case "1": 
				y_ = y0 - 3;
				x_ = x0 + 3;
				jg.fillEllipse(x_,y_,2,2); 
				break;
			} 
		}  
		var r = {};
		r.x = x_;
		r.y = y_;
		return r;
	}
	_drawAll();
  }
   
  function _barClass(o){
	var i = o.bars.length + 1;
	var x = i*200, y = 33, w=111, h=100;	
	var btnID = o.id + "_bar"+i+1;
	var s = "";
			s += "<div>";
			s += "<button id='";
			s += btnID; 
			s += "'>";
			s += "[+note]";
			s += "</button>"; 
			s += "<button style='color:blue;' id='";
			btnID = o.id + "_bar"+i+2;
			s += btnID; 
			s += "'>";
			s += "mm";
			s += "</button>"; 
			s += "<button style='color:blue;' id='";
			btnID = o.id + "_bar"+i+3;
			s += btnID; 
			s += "'>";
			s += "ha";
			s += "</button>"; 
			s += "<button style='color:blue;' id='";
			btnID = o.id + "_bar"+i+4;
			s += btnID; 
			s += "'>";
			s += "s1";
			s += "</button>"; 
			s += "<button style='color:blue;' id='";
			btnID = o.id + "_bar"+i+5;
			s += btnID; 
			s += "'>";
			s += "s2";
			s += "</button>"; 
	var divMsgID = "id_div_bar_Msg_"+o.lineNum + "_"+"bar_"+i;
			s += "<div style='background-color:white;' id='";
			s += divMsgID;
			s += "'>mmm</div>";
	var divID = o.id + "_div_bar" + i;

			s += "bar# " + divID;
	var divBar = blo0.blMDiv(o,divID,s,x,y,w,h,"gold");   
	divBar.barNum = i;
	divBar.notes=[];
	divBar.divMsg = bl$(divMsgID);
	 
	bl$(o.id + "_bar"+i+1).onclick = function(_d){return function(){var note = new _noteClass(_d);	_d.notes.push(note);}}(divBar);
	bl$(o.id + "_bar"+i+2).onclick = function(){	return function(){_on_off_div(this,bl$(divMsgID));}	}(); 
	bl$(o.id + "_bar"+i+3).onclick = function(_d){return function(){_on_off_div(this,_d.handle);_on_off_div(this,_d.main);}	}(divBar); 
	bl$(o.id + "_bar"+i+4).onclick = function(_o,_d){return function(){_d.style.width="20px";_d.style.h="20px";}}(o,divBar); 
	bl$(o.id + "_bar"+i+5).onclick = function(_o,_d){return function(){_d.style.width="110px";_d.style.h="20px";}}(o,divBar); 
  }
  function _lineClass(o){
	var i = o.lines.length + 1;
	var x = 0, y = i*150, w=300, h=100;	
	var s = "";
			s += "<div>";
			s += "<button id='id_btn__lineClass_btn";
			s += i;
			s += 1;
			s += "'>[+bar]</button>"; 
			s += "<button style='color:red;' id='id_btn__lineClass_btn";
			s += i;
			s += 2;
			s += "'>b2</button>"; 
			s += "<div style='background-color:red;' id='id_div_line_Msg";
			s += i;
			s += "'></div>";

			s += "Line# " + i;
	var d = blo0.blMDiv(o,"id_div__lineClass_"+i,s,x,y,w,h,"blue");   
	d.lineNum = i;
	d.bars=[];
	bl$("id_btn__lineClass_btn"+i+1).onclick = function(_d){
		return function(){  
				var bar = new _barClass(_d);
				_d.bars.push(bar);
		}
	}(d);
	bl$("id_btn__lineClass_btn"+i+2).onclick = function(_i,_idMsg){
		return function(){bl$(_idMsg).innerHTML = this.id + ":" + _i;}
	}(i,"id_div_line_Msg"+i);
  }
  function _UIClass(){   
	var w		= null;
    this.blrView	= function(b,d)
    { 
		if(w==null){	var s = "";
			s += "<div>";
			s += "<button id='id_btn_blrView_b3_btn1'>b1</button>";
			s += "<button id='id_btn_blrView_b3_btn2'>b2</button>";
			s += "<button id='id_btn_blrView_b3_btn3'>b3</button>";
			s += "<button id='id_btn_blrView_b3_btn4'>b4</button>";
			s += "<button id='id_btn_blrView_b3_btn5'>+</button>";
			s += "</div>";	
			s += "<div id='id_div_blrView_d2'>";
			s += "<button id='id_btn_blrView_d2_add_line'>[+line]</button>"; 
			s += "</div>";	
			w = blo0.blMDiv(document.body,"id_div__myWrap",s,10,50,400,200,"brown"); w.style.zIndex = -99; 
			bl$("id_btn_blrView_b3_btn1").onclick = function(){		w.jg.set(0,40,400,300);			} 
			bl$("id_btn_blrView_b3_btn2").onclick = function(){		w.jg.set(0,50,600,400);			}
			bl$("id_btn_blrView_b3_btn3").onclick = function(){		w.jg.set(0,50,800,600);			}    
			bl$("id_btn_blrView_b3_btn4").onclick = function(){	_on_off_div(this,w.handle);_on_off_div(this,w.main); } 
			bl$("id_btn_blrView_b3_btn5").onclick = function(){	_on_off_div(this,bl$("id_div_blrView_d2")); } 
			bl$("id_btn_blrView_d2_add_line").onclick = function(){
				if(!w.lines) w.lines=[];
				var l = new _lineClass(w);
				w.lines.push(l);
			}  
			w.jg		= new _jgClass(w,0,55,300,200,blColor[3]); 
			bl$("id_btn_blrView_b3_btn4").click();
		}
	  _on_off_div(b,w);
    }
    this.blrSet0	= function(b,d)    {		
		var tb = blo0.blDiv(d,"id_div_toolbar_function_f2_blrSet0","",blGrey[5]);
		b.style.background = "gray";
		var _id = "id_btn_f2_toolbar_blrSet0_b";
  
	}  
    this.blrSet1	= function(b,d)    {		
		var tb = blo0.blDiv(d,"id_div_toolbar_function_f2_blrSet1","",blGrey[5]);
		b.style.background = "gray"; 
		var _id = "id_btn_f2_toolbar_blrSet1_b";

		var b1 = blo0.blBtn(tb,_id+1,"b1",blGrey[0]);b1.onclick = function(){
			var d = blo0.blMDiv(w,"id_div_blrSet1_d1","1:",10,50,100,200,"purple");  
			_on_off_div(this,d);			
		}	
		var b2 = blo0.blBtn(tb,_id+2,"b2",blGrey[0]);b2.onclick = function(){
			var d = blo0.blMDiv(w,"id_div_blrSet1_d2","2:",50,50,100,200,"blue");  
			_on_off_div(this,d);}	
		var b3 = blo0.blBtn(tb,_id+3,"b3",blGrey[0]);b3.onclick = function(){ 
			var s = "";
			s += "<div>";
			s += "<button id='id_btn_blrSet1_b3_btn1'>b1</button>";
			s += "<button id='id_btn_blrSet1_b3_btn2'>b2</button>";
			s += "<button id='id_btn_blrSet1_b3_btn3'>b3</button>";
			s += "</div>";
			var d = blo0.blMDiv(w,"id_div_blrSet1_d3",s,110,50,100,200,"green");  
			bl$("id_btn_blrSet1_b3_btn1").onclick = function(){				d.main.style.backgroundColor="red";			}
			bl$("id_btn_blrSet1_b3_btn2").onclick = function(){				d.handle.style.backgroundColor="purple";	}
			bl$("id_btn_blrSet1_b3_btn3").onclick = function(){		_on_off_div(this,d.handle);_on_off_div(this,d.main);	}
			_on_off_div(this,d);
		}	
	}  
    this.blr_AboutMe = function(b,d){
	  var s = _v; 
	  s += "<br>music staff<br>";  
	  s += blo0.blhMakeLink(" f2.js ","https://littleflute.github.io/vc6/XdHtml/plx/design/f2.js","color:lightblue;","_blank");
	  s += blo0.blhMakeLink(" f2.js* ","https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f2.js","color:lightblue;","_blank");
      d.innerHTML = s;  
	  _on_off_div(b,d);
    };
  }
  var _myUI = function(b,d){ 
      _myView	= blo0.blDiv(d,d.id + "_myView","_myView",blGrey[5]);
	  if(!_myView.blFirst){
		blo0.blShowObj2Div(_myView,_ui);
		_myView.blFirst = true;
		blr_AboutMe.click();
		blrSet0.click();
		blrSet1.click();
	  }
	  _on_off_div(b,d);
  };
  _myUI(b,d);
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f2 = f2;
	ta.value = ta.f2;
}
