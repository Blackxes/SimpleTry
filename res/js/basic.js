// vordefinierte Variablen
var maxTitleLength		= 8;				// maximallaenge vom Titel

//_______________________________________________________________________________________________________________
// Liste runterklappem
function toggleVarList()
{
	$(".list").on("click", function()
	{
		$(this).toggleClass( "open" );
		$(this).find( "th:nth-child(4)" ).toggleClass( "open" );
		$(this).find( "th div" ).toggleClass( "open" );
	});

} // toggleVarList 
//

//_______________________________________________________________________________________________________________
// Text kuerzen
function cutString()
{
	csSupport('#log', 'th > h4', maxTitleLength);

} // cutString
//

//============================================================================
// 
function csSupport(searchArea, tagPath, maxLength)
{
	val = $(searchArea).find(tagPath);

	for (var i = 0; i < val.length; i++)
	{
		if (val[i]['textContent'].length > maxLength)
		{
			var title = val[i]['textContent'];
			var tempVal = val[i]['textContent'].substring(0, (maxLength - 2)) + '...';

			$(val[i]).text(tempVal).attr('title', title);
		}
	}

} // csSupport
//

//_______________________________________________________________________________________________________________
function cutLogText()
{
	// Liste der p's
	var listOfP = $('#log').find('th > p');

	for (var i = 0; i < listOfP.length; i++)
	{
		// Variablen
		var LogTag			= $(listOfP[i]).parent().parent();
		var LogWidth		= LogTag[0]['clientWidth'];
		var TitleTag 		= $(LogTag.find('h4'));
		var TitleWidth 		= TitleTag[0]['clientWidth'];
		var TextTag			= $(listOfP[i]);
		var TextWidth		= TextTag[0]['clientWidth'];

		// maximallaenge des Textes
		var MaxTextWidth = LogWidth - TitleWidth - 50 + 'px';

		$(TextTag).css('max-width', MaxTextWidth);
	}

} // 
//

//_______________________________________________________________________________________________________________
// wenn bildschirmgroesse veraendert wird
$( window ).resize(function() {
	cutLogText();
});

//_______________________________________________________________________________________________________________
// 
$( document ).ready(function() 
{
	// Liste runterklappen
	toggleVarList();

	// Text kuerzen
	cutString();
	cutLogText();

});