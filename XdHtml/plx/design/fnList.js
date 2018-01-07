var ls = [
	"f0.js",
	"f1.js",
	"f2.js",
	"f3.js",
	"f4.js",
	"f5.js",
	"f6.js",
	"f7.js",
];
var ld = bl$("id_div_function_list");
if(ld){
	ld.innerHTML = "v0.0.24 ";
	var lv = blo0.blDiv(ld,ld.id+"_lv_","lv",blGrey[5]);
	for(i in ls){
		var b = blo0.blBtn(ld,"id_div_function_"+i,"f"+i,blColor[i]);
		b.onclick = function(n_){
			return function(){
				var idScript = "id_script_f" + n_; 
				if(bl$(idScript)){
					var ta = bl$( "id_ta_4_NewClass" );
					var s = "ta.value = ta.f" + n_;
					eval(s);
				}
				else{
					s = blPath + "plx/design/f" + n_ + ".js";
					lv.innerHTML = s;

					blo0.blScript(idScript,s);
				}
			}
		}(i);
	}
}
