var f0 = function(b,d){
	//f0.js v0.0.2
	d.innerHTML = "f0.js: ->" + b.id + ":" + d.id;
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f0 = f0;
	ta.value = ta.f0;
}
