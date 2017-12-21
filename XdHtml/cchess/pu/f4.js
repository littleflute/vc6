var f4 = function(b,d){
	//f4.js v0.0.2
	d.innerHTML = "f4.js: ->" + b.id + ":" + d.id;
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f4 = f4;
	ta.value = ta.f4;
}
