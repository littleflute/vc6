var f2 = function(b,d){
	//f2.js v0.0.2
	d.innerHTML = "f2.js: ->" + b.id + ":" + d.id;
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f2 = f2;
	ta.value = ta.f2;
}
