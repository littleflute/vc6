var f1 = function(b,d){
	//f1.js v0.0.2
	d.innerHTML = b.id + ":" + d.id;
};

var ta = bl$( "id_ta_4_NewClass" );
if( ta ){
	ta.f1 = f1;
	ta.value = ta.f1;
}
