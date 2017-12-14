 
function _blDesignClass(){
	var _v	= "v0.0.33"; 
	var _view		= null;
	this.blrNewClass	= function(b,d){
		var t = blo0.blTextarea(d, d.id + "ta" , "alert(1);" , blGrey[2]);
		t.style.width = "98%";
		var d1 = blo0.blBtn(d,d.id+"_d1","run","gray");
		d1.onclick = function(){
			eval(t.value);
		};
		var d2 = blo0.blBtn(d,d.id+"_d2","makeLink","gray");
		d2.onclick = function(){
			var l = blo0.blLink(d,d.id+"_link","link",t.value,"Salmon");
		};
		_on_off_div(b,d);
	};
	this.bll7 = "-7--";
	this.blrRef4	= function(b,d){
		var t = blo0.blTextarea(d, d.id + "ta" , "https://littleflute.github.io/blog/docs/2017/05/05/" , blGrey[2]);
		t.style.width = "98%"; 
		var d2 = blo0.blBtn(d,d.id+"_d2","makeLink","gray");
		d2.onclick = function(){
			var l = blo0.blLink(d,d.id+"_link","link",t.value,"Salmon");
		};
		_on_off_div(b,d);
	};
	this.bll6 = "-6--";
	this.blrRef3	= function(b,d){
		var t = blo0.blTextarea(d, d.id + "ta" , "https://littleflute.github.io/blog/docs/2017/04/27/" , blGrey[2]);
		t.style.width = "98%"; 
		var d2 = blo0.blBtn(d,d.id+"_d2","makeLink","gray");
		d2.onclick = function(){
			var l = blo0.blLink(d,d.id+"_link","link",t.value,"Salmon");
		};
		_on_off_div(b,d);
	};
	this.bll5 = "-5--";
	this.blrRef2	= function(b,d){
		var t = blo0.blTextarea(d, d.id + "ta" , "https://littleflute.github.io/blog/docs/2017/04/22/" , blGrey[2]);
		t.style.width = "98%"; 
		var d2 = blo0.blBtn(d,d.id+"_d2","makeLink","gray");
		d2.onclick = function(){
			var l = blo0.blLink(d,d.id+"_link","link",t.value,"Salmon");
		};
		_on_off_div(b,d);
	};
	this.bll4 = "-4--";
	this.blrRef1	= function(b,d){
		var t = blo0.blTextarea(d, d.id + "ta" , "https://littleflute.github.io/blog/docs/2017/04/24/" , blGrey[2]);
		t.style.width = "98%"; 
		var d2 = blo0.blBtn(d,d.id+"_d2","makeLink","gray");
		d2.onclick = function(){
			var l = blo0.blLink(d,d.id+"_link","link",t.value,"Salmon");
		};
		_on_off_div(b,d);
	};
	this.bll3a = "-3a--";
	this.blrUpdate	= function(b,d){
		var t = blo0.blTextarea(d, d.id + "ta" , "https://github.com/littleflute/vc6/edit/master/XdHtml/plx/design.js" , blGrey[2]);
		t.style.width = "98%"; 
		var d2 = blo0.blBtn(d,d.id+"_d2","makeLink","gray");
		d2.onclick = function(){
			var l = blo0.blLink(d,d.id+"_link","link",t.value,"Salmon");
		};
		_on_off_div(b,d);
	};
	this.bll3 = "-3--";
	this.blr2DoList	= function(b,d){
		var s = "";
		s += "1. Design new javascript class online.<br>";
		s += "2. when visit in blVC6APP, it can save files.<br>";
		d.innerHTML = s;
		_on_off_div(b,d);
	};
	this.bll1 = "---";
	this.blrAboutMe	= function(b,d){
		var s = "";
		s += "1. blPlx: _blDesignClass.<br>";
		s += "2. by littleflute 2017/12/14 13:46 bjt.<br>";
		s += "3. source: <a href='plx/design.js' style='color:blue;'>design.js</a>.<br>";
		s += "4. <a href='http://www.beautifullover.org'style='color:lightblue;'>www.beautifullover.org</a>.<br>";
		d.innerHTML = s;
		_on_off_div(b,d); 
	}; 
	this.bll2 = "---";
	this.blrClose	= function(b,d){
		d.parentNode.parentNode.style.display = "none";
	};
	this.blhRun		= function()
	{
		if(_view == null)
		{
			_view = blo0.blMDiv(document.body,"id_div_plx__blDesignClass","_blDesignClass:" + _v,550,50,400,200,blColor[4]);
			var d = blo0.blDiv(_view,_view.id+"_showMyObj","showMyObj",blGrey[0]);
			blo0.blShowObj2Div(d,this);
			bl$("blrAboutMe").click();
			bl$("blr2DoList").click();
		}
	}
}
var o = new _blDesignClass; 
o.blhRun();

 
