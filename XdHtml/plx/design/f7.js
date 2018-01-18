var f6 = function(b,d){
	//f6.js		xxx  
	var _v			= "v0.0.115";  
	if(!d.v){
		b.innerHTML = "blPlayer" + _v;
		d.v = blo0.blDiv(d,d.id+"v","v:","blue");
		d.oUI = new _uiClass;
		blo0.blShowObj2Div(d.v,d.oUI);
		bl$("blr_AboutMe").click();
	}
	_on_off_div(b,d);
	function _uiClass(){
		this.v = "v0.0.25";
		this.blr_AboutMe = function(b,d){
		  var s = _v; 
		  s += "<br>music staff<br>";  
		  s += blo0.blhMakeLink(" f7.js ","https://littleflute.github.io/vc6/XdHtml/plx/design/f7.js","color:lightblue;","_blank");
		  s += blo0.blhMakeLink(" f7.js* ","https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f7.js","color:lightblue;","_blank");
		  d.innerHTML = s;  
		  _on_off_div(b,d);
		};
	}
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f6 = f6;
	ta.value = ta.f6;
}
