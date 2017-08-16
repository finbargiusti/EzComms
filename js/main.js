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
