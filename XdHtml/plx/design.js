 
function _blDesignClass(){
	var _v	= "v0.0.17"; 
	var _view		= null;
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
		}
	}
}
var o = new _blDesignClass; 
o.blhRun();

 