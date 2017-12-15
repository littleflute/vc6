var f6 = function(b,d){
	//f6.js v0.0.2
	d.innerHTML = "f6.js: ->" + b.id + ":" + d.id;
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f6 = f6;
	ta.value = ta.f6;
}
