var f6 = function(b,d){
	//f6.js		klines  
	var _v			= "v0.0.141";  
	if(!d.v){
		b.innerHTML = "blklines" + _v;
		d.v = blo0.blDiv(d,d.id+"v","v:","blue");
		d.oUI = new _uiClass;
		blo0.blShowObj2Div(d.v,d.oUI);
		bl$("blr_AboutMe").click();
	}
	_on_off_div(b,d);
	function _uiClass(){ 
		this.blr_NowXau	= function(b,d){ _initNow(b,d,"http://api.baidao.com/api/hq/npdata.do?ids=201");}
		this.bll2="--2--";
		this.blr_Now202	= function(b,d){ _initNow(b,d,"http://api.baidao.com/api/hq/npdata.do?ids=202");}
		this.bll1="--1--";
		this.blr_AboutMe = function(b,d){
		  var s = _v; 
		  s += "<br>music staff<br>";  
		  s += blo0.blhMakeLink(" f6.js ","https://littleflute.github.io/vc6/XdHtml/plx/design/f6.js","color:lightblue;","_blank");
		  s += blo0.blhMakeLink(" f6.js* ","https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f6.js","color:lightblue;","_blank");
		  d.innerHTML = s;  
		  _on_off_div(b,d);
		};
		function _initNow(b,d,url){ 
			if(!d.v){ 
				d.v = blo0.blDiv(d,d.id+"v","","brown");
				d.o = new _nowClass(d.v,url); 
			} 
			_on_off_div(b,d);			
		}
	}
	function _nowClass(_v,_url){
		var url = _url; 
		var v	= _v
		v.tb = blo0.blDiv(v,v.id+"tb","tb:","gray");
		v.v = blo0.blDiv(v,v.id+"v","v.v:","gray");
		v.tb.getData = blo0.blBtn(v.tb,v.tb.id+"getData","getData",blGrey[0]);
		v.tb.getData.n = 0;
		v.tb.getData.txt = "getData ";
		var _w = new _ajxWorkerClass(v.v,v.tb.getData);
		v.tb.getData.onclick = function(){	
			this.n++;
			this.innerHTML = this.txt + this.n;				 
			var s = url + "&t=" + new Date;
			blo0.blAjx(_w,s); 
		}
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
	ta.f6 = f6;
	ta.value = ta.f6;
}
