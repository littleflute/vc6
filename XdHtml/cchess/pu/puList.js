var ls = [
	"f0.js",
	"f1.js",
	"f2.js",
	"f3.js",
	"f4.js",
	"f5.js",
	"f6.js",
];
var ld = bl$("id_div_pu_list");

if(ld){
	ld.innerHTML = "v0.0.35 ";
	var lv = blo0.blDiv(ld,ld.id+"_lv_","lv",blGrey[5]);
	var div4TA = blo0.blDiv(ld,ld.id+"div4TA","div4TA",blGrey[1]);
	var divToolBar = blo0.blDiv(ld,ld.id+"divToolBar","divToolBar",blGrey[5]);
	var ta = blo0.blTextarea(div4TA,"id_ta_4_puList","pu",blGrey[3]);
	ta.style.width = "100%";
	ta.style.height = "200px";
	for(i in ls){
		var b = blo0.blBtn(ld,ld.id+"_btn_"+i,"f"+i,blGrey[0]);
		b.onclick = function(n_){
			return function(){
				var idScript = "id_script_f" + n_; 
				if(bl$(idScript)){
					var ta = bl$( "id_ta_4_puList" );
					var s = "ta.value = ta.f" + n_;
					eval(s);
				}
				else{
					s = "pu/f" + n_ + ".js";
					lv.innerHTML = s;

					blo0.blScript(idScript,s);
				}
			}
		}(i);

	}
	
	var btnParsePu = blo0.blBtn(divToolBar,divToolBar.id+"btnParsePu","btnParsePu",blGrey[0]);
	btnParsePu.onclick = function(n_){
		var ta = bl$( "id_ta_4_puList");		
		var txt = "var f = " + ta.value; 
		eval(txt);
		var s = f();
		var a = s.split("+");
		for(i in a){
			var b = blo0.blBtn(divToolBar,divToolBar.id+"_pu_btn_"+i,a[i],blGrey[0]);
			b.onclick = function(_btn){
				return function(){ 
				    var t = _btn.innerHTML;
					var a = t.charAt(0);
					var l1 = a.toLowerCase(); 
					var a = t.charAt(1);
					var l2 = a.toLowerCase(); 
					var a = t.charAt(3);
					var l3 = a.toLowerCase(); 
					var a = t.charAt(4);
					var l4 = a.toLowerCase();  
					ld.board.blhGo(ld.board,l1,l2,l3,l4);
				}
			}(b);
			
		}
	};
}
