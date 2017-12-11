 //  blo0.blLink(nav,"../../../../../../../xd/js/plx/xdPlxSpiter.js","cchess.html",url,"skyblue"); 
 //  blo0.blLink(nav,"../../../../../../../xd/js/plx/xdPlxSong.js","cchess.html",url,"skyblue");  

function _xdClass(){
	var _xdClassV	= "v0.1.5";
	var divWrap = document.getElementById("xddbg");
	var refreshTimes = 0;
	
	this.bll2 = "---";
	this.blrMyLinks = function(b,d){
		
	}
	this.blrRunJS = function(blrRunJSB,blrRunJSV){
		var t = blo0.blTextarea(blrRunJSV,"id_ta_xd_RunJS","alert('xd');","Aquamarine");	 
		t.style.width = "100%";
		t.style.height = "300px"; 

		var b = blo0.blBtn(blrRunJSV,blrRunJSB.id+"_BtnRun","run","green");		
		b.onclick = function(){eval(t.value);}	

		var btnPlx1 = blo0.blBtn(blrRunJSV,blrRunJSB.id+"btnPlx1","btnPlx1","lightblue");		
		btnPlx1.onclick = function(src_){ 
			var src = src_;
			return function(){
				blo0.blScript("id_script_xd_Plx1",src);
			}			 
		}("file:///C:/Users/13699/xd/js/plx/xdPlx1.js");

		var btnPlxOnline1 = blo0.blBtn(blrRunJSV,blrRunJSB.id+"btnPlxOnline1","btnPlxOnline1","skyblue");		
		btnPlxOnline1.onclick = function(src_){ 
			var src = src_;
			return function(){
				blo0.blScript("id_script_xd_Plx1",src);
			}			 
		}("https://littleflute.github.io/xd/js/plx/xdPlx1.js");
		_on_off_bd(blrRunJSB,blrRunJSV);
	};
	this.bll1 = "bll1";
	this.blhClassName = "_xdClass";

	function _getParentPath() {
		var d = document.getElementById("pageLevel");
		if(!d) return;
		var pageLevel = d.innerHTML;

		var r = "";
		var i = 0;
		while(i<pageLevel)
		{
			i++;
			r += "../";
		}
		return r;
	}
    

	function _makeToolBar2ShowObj(blo,d,o2Show) {
		var id = d.id;
		id += "_b1";
		var b1 = blo.blBtn(d,id,"+","red");
		b1.onclick = function(btn_){
			var v = null;
			return function(){
				v = blo.blDiv(d,btn_.id+"_div_View","b1v","green");
				blo.blShowObj2Div(v,o2Show);
				_on_off_bd(btn_,v);
			}
		}(b1);
	}
    

	function _xd_tool_bar(blo,d,o2Show) {
		var id = "";
		id = d.id + "_b1";
		var b1 = blo.blBtn(d,id,"+","red");
		b1.onclick = function(btn_){
			var v = null;
			return function(){
				v = blo.blDiv(d,btn_.id+"_div_View","b1v","green");
				blo.blShowObj2Div(v,o2Show);
				_on_off_bd(btn_,v);
			}
		}(b1);
		var _load_plx_btn = function(isOnLine,oBoss,plxName,src, color ){
			var idBtn	= oBoss.id + plxName + "btn" + isOnLine;
			var b		=  blo.blBtn(oBoss,idBtn,plxName,color);
			b.onclick = function(btn_){
				var v = null;
				var n = 0; 
				return function(){
					n++; 
					var idWrap	= oBoss.id + plxName + "wrap";
					v = blo.blDiv(oBoss,idWrap,"","green");  
					var srcHTML = "<a target='_blank' href=" + src + " style='color:white;'>" + plxName + "-source</a>";
					var ds	= blo.blDiv(v,oBoss.id + plxName + "src",srcHTML,"gray");

					var id		= "id_div_" + plxName;
					var dPlx = blo.blDiv(v,id,plxName + ":" + n,"gray"); 
					blo0.blScript("id_script_" + plxName,src);
					_on_off_div(btn_,v);
				}
			}(b);
		};
		_load_plx_btn(0,d,"_xdPlxSpiter","file:///C:/Users/13699/xd/js/plx/xdPlxSpiter.js","brown"); 
		_load_plx_btn(0,d,"_xdPlxSet","file:///C:/Users/13699/xd/js/plx/xdPlxSet.js","brown"); 
		_load_plx_btn(0,d,"_xdPlxSong","file:///C:/Users/13699/xd/js/plx/xdPlxSong.js","brown"); 
		_load_plx_btn(1,d,"_xdPlxSpiter","https://littleflute.github.io/xd/js/plx/xdPlxSpiter.js","lightblue"); 
		_load_plx_btn(1,d,"_xdPlxSet","https://littleflute.github.io/xd/js/plx/xdPlxSet.js","lightblue"); 
	}
    
	function _init(this_){
		if(QueryString.r)
		{
			refreshTimes = parseInt(QueryString.r) + 1;
		}
		else
		{
			refreshTimes = 0;
		}
		var pv = document.getElementById("idDivBlV");
		var _blPageV = pv?pv.innerHTML:"v0.0.0";
		var blInf = "page:" + _blPageV;
		blInf += "  xd.js: " + _xdClassV + "  refreshTimes="+refreshTimes;
		_xdDbgMsg(blInf); 
		_makeWrapContent(this_);
		divWrap.style.border = "1px red solid";
		divWrap.style.backgroundColor = "mediumseagreen";
	}
	function _xdDbgMsg(str)
	{
		if(divWrap){
			var s = xddbg.innerHTML;
			s += str;
			s += "<br>";
			divWrap.innerHTML =s;
		}
	}

	
	function _create_nav_4_pc(nav)
	{
		var _parentPath	= _getParentPath();
			var l	= [];
			var url = _parentPath + "index.html?r="+refreshTimes;
			var index = blo0.blLink(nav,"index.html","index.html",url,"DarkCyan");l.push(index);
			var url = _parentPath + "1.html";
			var l1 = blo0.blLink(nav,"1.html","1.html*",url,"white");		l.push(l1);
			var url = _parentPath + "2.html";
			var l2 = blo0.blLink(nav,"2.html","2.html*",url,"white");		l.push(l2);
			var url = _parentPath + "jsgraphics.html";
			var jsgraphics = blo0.blLink(nav,"jsgraphics.html","jsgraphics.html",url,"greenyellow");l.push(jsgraphics);
			var url = _parentPath + "kLines.html";
			var kLines = blo0.blLink(nav,"kLines.html","kLines.html",url,"skyblue"); l.push(kLines);		
			var url = _parentPath + "vc6ui.html";
			var vc6ui = blo0.blLink(nav,"vc6ui.html","vc6ui.html",url,"skyblue"); l.push(vc6ui);			
			var url = _parentPath + "lyric.html";
			var lyric = blo0.blLink(nav,"lyric.html","lyric.html",url,"skyblue"); l.push(lyric);			
			var url = _parentPath + "song.html";
			var song = blo0.blLink(nav,"song.html","song.html",url,"skyblue"); l.push(song);
			var url = _parentPath + "player.html";
			var player = blo0.blLink(nav,"player.html","player.html",url,"skyblue"); l.push(player);
			var url = _parentPath + "cchess/index.html";
			var cchess = blo0.blLink(nav,"cchess/index.html","cchess.html",url,"skyblue"); l.push(cchess);
			
			
			var a = nav.getElementsByTagName('a');
			var _title = document.title;
			for(i in l)
			{ 
				var m = a;
				m[i].style.color = "white";
				m[i].style.backgroundColor = _title==m[i].id?"red":"black"; 
				m[i].onmouseover = function(){
					if(_title==this.id){
						this.style.backgroundColor = "red";
					} 
					else {
						this.style.backgroundColor = "ForestGreen";
					}
				};
				m[i].onmouseout = function(){ 
					if(_title==this.id){
						this.style.backgroundColor = "red";
					} 
					else {
						this.style.backgroundColor = "black";
					}
				}; 
				m[i].onclick = function(){   
			//		this.href += "?c=" + this.id;
				};
			}
	}
		
	
	function _create_nav_4_online(nav)
	{
		var _parentPath	= _getParentPath();
			var l	= [];
			var url = "https://littleflute.github.io/xd/";
			var xd = blo0.blLink(nav,"xd","xd",url,"DarkCyan");l.push(xd);

			var url = "https://littleflute.github.io/blog/";
			var blog = blo0.blLink(nav,"blog","blog",url,"DarkCyan");l.push(blog);

			var url = "https://littleflute.github.io/cchess/";
			var cchess = blo0.blLink(nav,"cchess","cchess",url,"DarkCyan");l.push(cchess);

			var url = "https://littleflute.github.io/vc6/";
			var vc6 = blo0.blLink(nav,"vc6","vc6",url,"DarkCyan");l.push(vc6);

			var url = "https://littleflute.github.io/bible/";
			var bible = blo0.blLink(nav,"bible","bible",url,"DarkCyan");l.push(bible);

			var a = nav.getElementsByTagName('a');
			var _title = document.title;
			for(i in l)
			{ 
				var m = a;
				m[i].style.color = "white";
				m[i].style.backgroundColor = _title==m[i].id?"red":"black"; 
				m[i].onmouseover = function(){
					if(_title==this.id){
						this.style.backgroundColor = "red";
					} 
					else {
						this.style.backgroundColor = "skyblue";
					}
				};
				m[i].onmouseout = function(){ 
					if(_title==this.id){
						this.style.backgroundColor = "red";
					} 
					else {
						this.style.backgroundColor = "black";
					}
				}; 
				m[i].onclick = function(){   
				//	this.href += "?c=" + this.id;
				};
			}
	}	
	function _makeWrapContent(this_)
	{
		if(divWrap)
		{ 
			_xd_tool_bar(blo0,blo0.blDiv(divWrap,"xdNav1","==","DarkCyan"),this_);
			_create_nav_4_online(blo0.blDiv(divWrap,"_create_nav_4_online","online::","green")); 
			_create_nav_4_pc(blo0.blDiv(divWrap,"_create_nav_4_pc","pc::","gold")); 
		}
	}
	_init(this);
}
var xdobj = new _xdClass; 

 