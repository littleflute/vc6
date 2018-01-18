var f7 = function(b,d){
	//f7.js		blSpiter  
	var _v			= "v0.0.134";  
	if(!d.v){
		b.innerHTML = "blPlayer" + _v;
		d.v = blo0.blDiv(d,d.id+"v","v:","blue");
		d.oUI = new _uiClass;
		blo0.blShowObj2Div(d.v,d.oUI);
		bl$("blr_AboutMe").click();
	}
	_on_off_div(b,d);
	function _uiClass(){ 
		var url = "http://www.xqbase.com/xqbase/?gameid=";
		var ta	= null;
		var n	= 0;
		var str = null;
		this.blr_MakeTA = function(b,d){ 
		  if(!d.v){   
				d.v = blo0.blDiv(d,d.id+"v","","brown");
				ta = blo0.blTextarea(d.v,d.v.id + "_ta_4_data","",blGrey[3]);
				ta.style.width	= "100%";
				ta.style.height = "300px"; 
			} 
			_on_off_div(b,d);
		};
		this.bll1="--1--";
		this.blr_GetData = function(b,d){  	
			if(!str) str = b.innerHTML;
				var _w = new _ajxWorkerClass(0,0);
				_w._2do	= function(txt)
				{ 
					if(ta) ta.value = txt;
				} 			 
				n++;
				b.innerHTML = str + n;
				var sURL = url + n;
				blo0.blAjx(_w,sURL);  
		};
		this.blr_AboutMe = function(b,d){
		  var s = _v; 
		  s += "<br>music staff<br>";  
		  s += blo0.blhMakeLink(" f7.js ","https://littleflute.github.io/vc6/XdHtml/plx/design/f7.js","color:lightblue;","_blank");
		  s += blo0.blhMakeLink(" f7.js* ","https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f7.js","color:lightblue;","_blank");
		  d.innerHTML = s;  
		  _on_off_div(b,d);
		};
	}
	function _ajxWorkerClass(_v,_btn){
		var v = _v;
		this._2do	= function(txt)
		{
			v.innerHTML = txt; 
			_btn.click();
		} 
	}
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f7 = f7;
	ta.value = ta.f7;
}
