// Declarations

var header = document.querySelector("#header h1");
var title = "EzComms";

// Functions

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

(async function() {
	var breakTime = 130;
	await sleep(1000);
	for (var i = 0; i <= title.length; ++i) {
		await sleep(breakTime)
		header.innerHTML = (title.slice(0, i) + "|")
	}
})();

window.onload = function() {
	console.log(window.innerWidth);
	if (window.innerWidth >= 1000) {
		console.log(document.getElementById("doc-nav").style.height);
		document.getElementById("doc-nav").style.height = document.getElementById("content-wrapper").clientHeight + "px";	
	}	
};

window.onresize = function() {
	if (window.innerWidth <= 1000) {
		console.log(document.getElementById("doc-nav").style.height);
		document.getElementById("doc-nav").style.height = "auto";	
		document.getElementById("doc-nav").style.width = "100%"
	} else {
		document.getElementById("doc-nav").style.height = document.getElementById("content-wrapper").clientHeight + "px";	
		document.getElementById("doc-nav").style.width = (window.innerWidth/5)+20 + "px";
	}
};