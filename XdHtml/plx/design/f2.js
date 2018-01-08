var f2 = function(b,d){
	//f2.js music staff
  var _v			= "v0.0.331";  

  var _ui = new _UIClass;
  function _noteClass(o){
	var i = o.notes.length + 1;
	var x = i*33, y = 100, w=41, h=100;	
	var btnID = o.id + "_note"+i+1;
	var s = "";
			s += "<div>";
			s += "<button id='";
			s += btnID; 
			s += "'>";
			s += "b1";
			s += "</button>"; 
			s += "<button style='color:red;' id='";
			btnID = o.id + "_note"+i+2;
			s += btnID; 
			s += "'>";
			s += "b2";
			s += "</button>"; 
	var divMsgID = o.id + "_"+"beat_"+i;
			s += "<div style='background-color:red;' id='";
			s += divMsgID;
			s += "'></div>";
	var divID = o.id + "_div_beat" + i;

			s += "beat# " + divID;
	var divBeat = blo0.blMDiv(o,divID,s,x,y,w,h,"gray");   
	divBeat.Num = i;
	divBeat.divMsg = bl$(divMsgID);
	 
	bl$(o.id + "_note"+i+1).onclick = function(_d){
		return function(){ 
			_d.divMsg.innerHTML = this.id + ":" + _d.Num;
		}
	}(divBeat);
	bl$(o.id + "_note"+i+2).onclick = function(_i,_idMsg){
		return function(){bl$(divMsgID).innerHTML = this.id + ":" + _i;}
	}(i,"id_div_bar_Msg"+i); 
  }
  function _barClass(o){
	var i = o.bars.length + 1;
	var x = i*200, y = 100, w=155, h=100;	
	var btnID = o.id + "_bar"+i+1;
	var s = "";
			s += "<div>";
			s += "<button id='";
			s += btnID; 
			s += "'>";
			s += "[+beat]";
			s += "</button>"; 
			s += "<button style='color:red;' id='";
			btnID = o.id + "_bar"+i+2;
			s += btnID; 
			s += "'>";
			s += "b2";
			s += "</button>"; 
	var divMsgID = "id_div_bar_Msg_"+o.lineNum + "_"+"bar_"+i;
			s += "<div style='background-color:red;' id='";
			s += divMsgID;
			s += "'></div>";
	var divID = o.id + "_div_bar" + i;

			s += "beat# " + divID;
	var divBar = blo0.blMDiv(o,divID,s,x,y,w,h,"gold");   
	divBar.barNum = i;
	divBar.notes=[];
	divBar.divMsg = bl$(divMsgID);
	 
	bl$(o.id + "_bar"+i+1).onclick = function(_d){
		return function(){ 
				var note = new _noteClass(_d);
				_d.notes.push(note);
		}
	}(divBar);
	bl$(o.id + "_bar"+i+2).onclick = function(_i,_idMsg){
		return function(){bl$(divMsgID).innerHTML = this.id + ":" + _i;}
	}(i,"id_div_bar_Msg"+i); 
  }
  function _lineClass(o){
	var i = o.lines.length + 1;
	var x = 0, y = i*110, w=300, h=100;	
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
			w.page = blo0.blDiv(w,w.id+"divView","",blGrey[0]);
			w.jg		= new _jgClass(w.page.id);
			w.jg.upate(); 
			bl$("id_btn_blrView_b3_btn3").click();
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
  function _jgClass(id){
	var _jg = new jsGraphics(id);
	var x=0,y=0,w=600,h=400;
	function _drawAll(){
		_jg.clear();
		_jg.setColor("gray");
		_jg.fillRect(x,y,w,h);
		_jg.paint();
	}   
	this.upate	= function()			{ _drawAll(); }   
	this.set	= function(x1,y1,w1,h1) { x=x1;y=y1;w=w1;h=h1; _drawAll(); }   
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
