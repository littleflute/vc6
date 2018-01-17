var f5 = function(b,d){
	//f5.js		player
  var _v			= "v0.0.112";  
	if(!d.v){
		b.innerHTML = "blPlayer" + _v;
		d.v = blo0.blDiv(d,d.id+"v","v:","blue");
		d.oUI = new _uiClass;
		blo0.blShowObj2Div(d.v,d.oUI);
		bl$("blr_CreatePlayer").click();
	}
	_on_off_div(b,d);
	function _uiClass(){
		this.v = "v0.0.23";
		this.blr_Play = function(b,d) {			
			var mp = bl$("id_Object_Player");
			if(mp){
				mp.controls.play();
			}
			else{
				mp = bl$("id_html5_player");
				mp.play();
			}
		}
		this.blr_Pause = function(b,d) {			
			var mp = bl$("id_Object_Player");
			if(mp){
				mp.controls.pause();
			}
			else{
				mp = bl$("id_html5_player");
				mp.pause();
			}
		}
		
		
		this.blr_CreatePlayer = function(b,d) { 
			if(!d.v){
				d.v = blo0.blDiv(d,d.id+"v","v:","red");
				var soundFile = "https://littleflute.github.io/bible1/NIV%20Live%20A%20Bible%20Experience/OldTestament/cd01/01 Genesis 1.mp3";
			
				try{
					var a = new Audio(soundFile);
					a.setAttribute("controls", "controls");
					a.setAttribute("id", "id_html5_player");
					d.v.appendChild(a);
				}
				catch(e){
					d.v.innerHTML = _makeMPObj(soundFile);
				}
			}
			_on_off_div(b,d);

			function _makeMPObj (strURL) {
				var strHtml;	
				strHtml ="<object id='id_Object_Player' width='400' height='64' classid='clsid:6bf52a52-394a-11d3-b153-00c04f79faa6'>";
    			strHtml+="<param name='url' value=\""+ strURL +"\">";
    			strHtml+="<param name='volume' value='10'>";
    			strHtml+="<param name='loop' value='true'>";
    			strHtml+="<param name='autoStart' value='0'>";
				strHtml+="</object>";     
				return strHtml;
			}
		}
	
    this.blr_AboutMe = function(b,d){
	  var s = _v; 
	  s += "<br>music staff<br>";  
	  s += blo0.blhMakeLink(" f5.js ","https://littleflute.github.io/vc6/XdHtml/plx/design/f5.js","color:lightblue;","_blank");
	  s += blo0.blhMakeLink(" f5.js* ","https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f5.js","color:lightblue;","_blank");
      d.innerHTML = s;  
	  _on_off_div(b,d);
    };
	}
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f5 = f5;
	ta.value = ta.f5;
}
