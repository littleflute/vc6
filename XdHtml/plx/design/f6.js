var f6 = function(b,d){
	//f6.js		klines  
	var _v			= "v0.0.222";  
	if(!d.v){
		b.innerHTML = "blklines" + _v;
		d.v = blo0.blDiv(d,d.id+"v","v:","blue");
		d.oUI = new _uiClass;
		blo0.blShowObj2Div(d.v,d.oUI);
		bl$("blr_AboutMe").click();
	}
	_on_off_div(b,d);
	function _uiClass(){ 
		this.blr_NowAll	= function(b,d){
			if(!d.v){ 
				var url = "http://api.baidao.com/api/hq/npdata.do?ids=";
				var n = 1;

				d.v = blo0.blDiv(d,d.id+"v","","brown");
				d.v.ta = blo0.blTextarea(d.v,d.v.id + "_ta_4_data","",blGrey[3]);
				
				var _w = new _ajxWorkerClass(0,0);
				_w._2do	= function(txt)
				{ 
					var s = "var o = " + txt;
					eval(s);
					if(o.length>0){
						var k = o[0];
						d.v.ta.value += n + ":" + k.name + "," + k.now + "\n";
					}
					b.innerHTML = n + "/1111";
					n++;
					if(n<1111){
						var sURL = url + n + "&t=" + new Date;
						blo0.blAjx(_w,sURL); 
					}
				} 			 
				var sURL = url + n + "&t=" + new Date;
				blo0.blAjx(_w,sURL); 
			} 
			_on_off_div(b,d);
		}
		this.bll3="--3--";
		this.blr_NowXau	= function(b,d){ _initNow(b,d,201);}
		this.bll2="--2--";
		this.blr_Now202	= function(b,d){ _initNow(b,d,202);}
		this.bll1="--1--";
		this.blr_AboutMe = function(b,d){
		  var s = _v; 
		  s += "<br>music staff<br>";  
		  s += blo0.blhMakeLink(" f6.js ","https://littleflute.github.io/vc6/XdHtml/plx/design/f6.js","color:lightblue;","_blank");
		  s += blo0.blhMakeLink(" f6.js* ","https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design/f6.js","color:lightblue;","_blank");
		  d.innerHTML = s;  
		  _on_off_div(b,d);
		};
		function _initNow(b,d,ids){ 
			if(!d.v){ 
				d.v = blo0.blDiv(d,d.id+"v","","brown");
				d.o = new _nowClass(d.v,ids); 
			} 
			_on_off_div(b,d);			
		}
	}
	function _nowClass(_v,ids){
		var url1 = "http://api.baidao.com/api/hq/npdata.do?ids=";
		var url2 = "http://api.baidao.com/api/hq/mtdata.do?quotationType=1&id=";
		var v	= _v
		v.tb = blo0.blDiv(v,v.id+"tb","tb:","gray");
		v.v = blo0.blDiv(v,v.id+"v","v.v:","brown");
		v.v.ta1 = blo0.blTextarea(v.v,v.v.id + "_ta_4_url1_data","",blGrey[3]);
		v.v.ta1.style.width = "100%";v.v.ta1.style.height = "200px";
		var b1 = blo0.blBtn(v.tb,v.tb.id+"getData","getData",blGrey[0]);
		b1.n = 0;
		b1.txt = "getData "; 
		b1.onclick = function(_w){
			return function(){
				this.n++;
				this.innerHTML = this.txt + this.n;			
				var url = url1 + ids; 	 
				var s = url + "&t=" + new Date;
				blo0.blAjx(_w,s); 
			}	
		}(new _ajxWorkerClass(v.v,b1));
		
		var b2 = blo0.blBtn(v.tb,v.tb.id+"mtdata","mtdata",blGrey[0]);
		b2.n = 0;
		b2.txt = "getData "; 
		b2.onclick = function(_w){
			return function(){
				this.n++;
				this.innerHTML = this.txt + this.n;			
				var url = url2 + ids; 	 
				var s = url + "&t=" + new Date;
				blo0.blAjx(_w,s); 
			}	
		}(new _mtdataAjxWorkerClass(v.v,b2));
	} 
	function _ajxWorkerClass(_v,_btn){
		var v = _v;
		this._2do	= function(txt)
		{
			v.ta1.innerHTML = txt; 
			_btn.click();
		} 
	}
	function _mtdataAjxWorkerClass(_v,_btn){
		var v = _v;
		v.ta2 = blo0.blTextarea(v,v.id + "_ta_4_url2_data","",blGrey[3]);
		v.ta2.style.width = "100%";
		v.ta2.style.height = "200px";
		this._2do	= function(txt)
		{
			v.ta2.innerHTML = txt; 
			_btn.click();
		} 
	}
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f6 = f6;
	ta.value = ta.f6;
}
