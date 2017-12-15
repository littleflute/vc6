var f3 = function(b,d){
	//f3.js v0.0.2
	d.innerHTML = "f3.js: ->" + b.id + ":" + d.id;
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f3 = f3;
	ta.value = ta.f3;
}
