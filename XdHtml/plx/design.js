 
function _blDesignClass(){
	var _v	= "v0.0.83"; 
	var _view		= null;
	var _loadFunList = function(d){
		var ld = blo0.blDiv(d,"id_div_function_list","ld",blGrey[5]);
		blo0.blScript("id_script_function_list","plx/design/fnList.js");
	}
	this.blrNewClass	= function(b,d){
		_loadFunList(d);
		var t = blo0.blTextarea(d, "id_ta_4_NewClass" , "alert(1);" , blGrey[2]);
		t.style.width = "98%";
		t.style.height = "200px";
		var _btnShow = blo0.blBtn(d,d.id+"_btnShow","show","gray");
		_btnShow.onclick = function(_div){
			var myView = null;
			var oNew   = {};
			oNew.v = "v0.0.3";
			return function()
			{
				if(myView == null)
				{
					var btn = [];
					var btnSel = null;
					myView = blo0.blMDiv(document.body,"id_div_New_Obj","NewObj:" + _v,750,50,400,200,blColor[4]);
					var _btnSet = blo0.blBtn(_div,_div.id+"_btnSet","SetFun",blGrey[2]);
					_btnSet.onclick = function(){
						if(btnSel==null) return;
						var s = "oNew.blrFun" + btnSel.n + "=" + t.value;
						eval(s);	 		
					}
					var _btnNewFun = blo0.blBtn(_div,_div.id+"_btnNewFun","newFun","gray");
					_btnNewFun.onclick = function(){
						var sf	= "";
						var n	= 0;
						var f = function(b,d){
						    d.innerHTML = d.id;		
						};
						return function(){
							n++;
							sf = "oNew.blrFun" + n + " = " + f;
							eval (sf);
							var b = blo0.blBtn(_div,_div.id+"_btn"+n,"f"+n,"gray");
							b.n = n;
							btn.push(b);
							b.onclick = function(btn_,n_){
								return function(){
									t.value = eval("oNew.blrFun"+n_);
									btnSel = btn_;
									btnSel
									for(var i = 0; i < btn.length; i++)
									{
										btn[i].style.backgroundColor = btnSel==btn[i]?blGrey[1]:blGrey[5];
									}	
								}
							}(b,n);
							_btnShow.click();
						}
					}();
				}
				var div2ShowObj = blo0.blDiv(myView,myView.id+"_showMyObj","showMyObj",blGrey[0]);
				blo0.blShowObj2Div(div2ShowObj,oNew); 
			}
		}(d);

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
	this.bll3b = "-3b--";
	this.blrLog	= function(b,d){
		var s = "";
		s += "2. 2017/12/16 1:39bjt_ update f1.js from ";
		s += "<a href='https://littleflute.github.io/blog/docs/2017/05/05/' style='color:blue;'>ref(blrRef4)</a><br>";
		s += "1. 2017/12/15 13:36bjt_ load function list from ";
		s += "<a href='plx/design/fnList.js' style='color:blue;'>fnList.js</a><br>";

		d.innerHTML = s;
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
			_view = blo0.blMDiv(document.body,"id_div_plx__blDesignClass","_blDesignClass:" + _v,150,50,400,200,blColor[4]);
			var d = blo0.blDiv(_view,_view.id+"_showMyObj","showMyObj",blGrey[0]);
			blo0.blShowObj2Div(d,this);
			bl$("blrAboutMe").click();
			bl$("blr2DoList").click();
		}
	}
}
var o = new _blDesignClass; 
o.blhRun();

 
