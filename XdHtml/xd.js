var QueryString = function () 
{
  var query_string = {};
  var query = window.location.search.substring(1);
  var vars = query.split("&");
  for (var i=0;i<vars.length;i++) {
    var pair = vars[i].split("=");
    if (typeof query_string[pair[0]] === "undefined") {
      query_string[pair[0]] = decodeURIComponent(pair[1]);
    } else if (typeof query_string[pair[0]] === "string") {
      var arr = [ query_string[pair[0]],decodeURIComponent(pair[1]) ];
      query_string[pair[0]] = arr;
    } else {
      query_string[pair[0]].push(decodeURIComponent(pair[1]));
    }
  } 
  return query_string;
}(); 

function _xdClass(){
	var _xdClassV = "v0.0.96";
	var divWrap = document.getElementById("xddbg");
	var refreshTimes = 0;
	this.blrRunJS = function(btn,view){
		var t = blo0.blTextarea(view,btn.id+"t1","alert('xd');","Aquamarine");	 
		t.style.width = "100%";
		t.style.height = "300px"; 

		var b = blo0.blBtn(view,btn.id+"_BtnRun","run","green");		
		b.onclick = function(){eval(t.value);}	
		_on_off_bd(btn,view);
	};
	this.bll1 = "bll1";
	this.blhClassName = "_xdClass";

	function _makeToolBar(blo,d) {
		var id = d.id;
		id += "_b1";
		var b1 = blo.blBtn(d,id,"+","red");
		b1.onclick = function(btn_){
			var v = null;
			return function(){
				v = blo.blDiv(d,btn_.id+"_div_View","b1v","green");
				blo.blShowObj2Div(v,xdobj);
				_on_off_bd(btn_,v);
			}
		}(b1);
	}
    

	function _init(){
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
		_makeWrapContent(blo0);
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


			
	function _makeWrapContent(blo0)
	{
		if(!blo0) return;

		if(divWrap)
		{
			var nav = blo0.blDiv(divWrap,"xdNav","::");
			var nav1 = blo0.blDiv(divWrap,"xdNav1","==","DarkCyan");
			var l	= [];
			var index = blo0.blLink(nav,"index.html","index.html","index.html?r="+refreshTimes,"DarkCyan");l.push(index);
			var l1 = blo0.blLink(nav,"1.html","1.html*","1.html","white");		l.push(l1);
			var l2 = blo0.blLink(nav,"2.html","2.html*","2.html","white");		l.push(l2);
			var jsgraphics = blo0.blLink(nav,"jsgraphics.html","jsgraphics.html","jsgraphics.html","greenyellow");l.push(jsgraphics);
			var kLines = blo0.blLink(nav,"kLines.html","kLines.html","kLines.html","skyblue"); l.push(kLines);
			//"vc6ui.html"
			var vc6ui = blo0.blLink(nav,"vc6ui.html","vc6ui.html","vc6ui.html","skyblue"); l.push(vc6ui);
			var lyric = blo0.blLink(nav,"lyric.html","lyric.html","lyric.html","skyblue"); l.push(lyric);
			var song = blo0.blLink(nav,"song.html","song.html","song.html","skyblue"); l.push(song);
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
					this.href += "?c=" + this.id;
				};
			}
			_makeToolBar(blo0,nav1);
		}
	}
	_init();
}
var xdobj = new _xdClass; 

 