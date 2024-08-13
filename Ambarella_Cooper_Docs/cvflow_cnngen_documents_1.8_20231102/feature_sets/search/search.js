/*******************************************************************************
 * search.js
 *
 * Copyright (c) 2021 Ambarella International LP
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP.
 *
 * This file includes sample code and is only for internal testing and evaluation.  If you
 * distribute this sample code (whether in source, object, or binary code form), it will be
 * without any warranty or indemnity protection from Ambarella International LP or its affiliates.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

var selectedFilter="#allFilter";
var searchDataList=[];
var searchResultList=[];
var curQueryList=[];
var searchFieldMap = [{type: "doc_page", strategy: "fullmatch", fields: ["alltext"]},
			{type: "module_page", strategy: "fullmatch", fields: ["text", "title"]},
			{type: "struct_page", strategy: "fuzzymatch", fields: ["alltext"]},
			{type: "file_page", strategy: "fuzzymatch", fields: ["alltext", "title"]},
			{type: "example_page", strategy: "fullmatch", fields: ["text", "title"]}]
var renderHeaderMap = [{type: "doc_page", header: "Documents", filter:"docFilter"},
			{type: "module_page", header: "Modules", filter:"moduleFilter"},
			{type: "struct_page", header: "Data Structures", filter:"structFilter"},
			{type: "file_page", header: "Source Files", filter:"sourceFilter"},
			{type: "example_page", header: "Examples", filter:"exampleFilter"}]

function SearchBox(name, resultsPath, inFrame, label)
{
	this.searchLabel = label;
	this.DOMSearchField = function()
	{
		return document.getElementById("MSearchField");
	}
	this.DOMSearchBox = function()
	{
		return document.getElementById("MSearchBox");
	}
	this.OnSearchFieldFocus = function(isActive)
	{
		if (isActive) {
			this.DOMSearchBox().className = 'MSearchBoxActive';
			var searchField = this.DOMSearchField();
			if (searchField.value == this.searchLabel) {
				searchField.value = '';
			}
		} else {
			this.DOMSearchBox().className = 'MSearchBoxInactive';
			this.DOMSearchField().value   = this.searchLabel;
		}
	}
	this.CloseResultsWindow =function()
	{
		return;
	}
}

function trim(s)
{
	return s?s.replace(/^\s\s*/, '').replace(/\s\s*$/, ''):'';
}

function getURLParameter(name)
{
	return decodeURIComponent((new RegExp('[?|&]'+ name +
		 '=' + '([^&;]+?)(&|#|;|$)').exec(location.search)
		 || [,""])[1].replace(/\+/g, '%20')) || null;
}

var signMap = {
	"&": "&amp;",
	"<": "&lt;",
	">": "&gt;",
	'"': '&quot;',
	"'": '&#39;',
	"/": '&#x2F;'
};

function signConvert(str)
{
	return String(str).replace(/[&<>"'\/]/g, function (str) {
		return signMap[str];
	});
}

function filterSearchResult(filter) {
	var filterResult = [];

	if (selectedFilter) {
		$(selectedFilter).removeClass('searchFilterSelected');
	}
	selectedFilter = '#' + event.target.id;
	$(selectedFilter).addClass('searchFilterSelected');

	if (filter == 'all') {
		filterResultList = searchResultList;
	} else {
		filterResultList = searchResultList.filter(obj => {
			return obj.type == filter;
		});
	}

	clearSearchResult();
	renderSearchResult(filterResultList, curQueryList);
}

function renderTypeStart(type)
{
	html = "<div class='typeHeader'>";
	html += "<span class='arrow' onclick='clickArrow(event)'>▼</span>";
	html += signConvert(type);
	html += "</div>";
	html += "<div class='content' style='display: block'>";

	return html;
}

function renderTypeStop(argument)
{
	return "</div>";
}

function renderHeaderStart(stype, section)
{
	html = "";

	html += "<div class='" + stype + "' onclick=''>";
	html += "<span class='arrow' onclick='clickArrow(event)'>▼</span>";
	html += "<a class='linkHeader' href='" + section.url +"'>"
	html += signConvert(section.title);
	html += "</a>"
	html += "</div>";

	html += "<div class='content' style='display: block'>";

	return html;
}

function renderHeaderStop()
{
	return "</div>";
}

function renderContent(section)
{
	html = "<div class='textResult'>";

	for (var i = 0; i < section.matchList.length; i++) {
		keyWordList = section.matchList[i].wordList;
		textStartIndex = section.matchList[i].quoteStart;
		if (i == 0 && textStartIndex != 0)
			html += "......"

		wordIndex = 0;
		while (wordIndex < keyWordList.length) {
			textEndIndex = keyWordList[wordIndex].wordStart;
			html += signConvert(section.text.substring(textStartIndex, textEndIndex));
			html += "<em class='keyWord'>";
			html += signConvert(section.text.substring(keyWordList[wordIndex].wordStart,
				keyWordList[wordIndex].wordEnd));
			html += "</em>";

			textStartIndex = keyWordList[wordIndex].wordEnd;
			wordIndex++;
		}

		textEndIndex = section.matchList[i].quoteEnd;
		html += signConvert(section.text.substring(textStartIndex, textEndIndex));
		if (textEndIndex != section.text.length)
			html += "......"
	}
	html += "</div>";

	return html;
}

function renderFilter(resultList)
{
	var resultHeader = document.getElementsByClassName("header")[0];

	if (resultHeader) {
		var resultTitle = resultHeader.getElementsByClassName("title")
		if (resultTitle && resultTitle[0].innerHTML == "Search Results") {
			var filterHtml = "<div id='filter' class='searchFilter'>\n"
			filterHtml += "    <div id='allFilter' class='searchFilterTab " +
				"searchFilterSelected'" +
				"onclick='filterSearchResult(\"all\")'>All (" +
				resultList.length + ")</div>\n"

			for (var i = 0; i < renderHeaderMap.length; i++) {
				var subsetResultList = resultList.filter(obj => {
					return obj.type == renderHeaderMap[i].type;
				});
				filterHtml += "<div id='" + renderHeaderMap[i].filter +
					"' class='searchFilterTab' onclick='filterSearchResult(\"" +
					renderHeaderMap[i].type + "\")'>" +
					renderHeaderMap[i].header +
					" (" + subsetResultList.length + ")</div>\n";
			}
			filterHtml += "</div>\n"

			resultHeader.innerHTML += filterHtml
		}
	}

	return;
}

function clickArrow(event)
{
	var content = event.target.parentElement.nextElementSibling;
	if (content.style.display == "block") {
		content.style.display = "none";
	} else {
		content.style.display = "block";
	}
	var arrow = event.target;
	if (arrow.innerHTML == "►") {
		arrow.innerHTML = "▼"
	} else {
		arrow.innerHTML = "►"
	}
}

function renderFileTree(fileList)
{
	renderStr = ""

	for (var i = 0; i < fileList.length; i++) {
		file = fileList[i];
		if (file.isHit || file.isChildHit) {
			renderStr += renderHeaderStart("fileHeader", file);
			if (file.isHit)
				renderStr += renderContent(file);
		}
		if (file.content) {
			for (var j = 0; j < file.content.length; j++) {
				section = file.content[j];
				if (section.isHit || section.isChildHit) {
					renderStr += renderHeaderStart("sectionHeader", section);
					if (section.isHit)
						renderStr += renderContent(section);
				}
				if (section.content) {
					for (var k = 0; k < section.content.length; k++) {
						subsection = section.content[k];
						if (subsection.isHit || subsection.isChildHit) {
							renderStr += renderHeaderStart("subSectionHeader", subsection);
							if (subsection.isHit) {
								renderStr += renderContent(subsection);
							}
						}
						if (subsection.content) {
							for (var u = 0; u < subsection.content.length; u++) {
								subsubsection = subsection.content[u];
								if (subsubsection.isHit || subsubsection.isChildHit) {
									renderStr += renderHeaderStart("subSubSectionHeader", subsubsection);
									if (subsubsection.isHit)
										renderStr += renderContent(subsubsection);
									renderStr += renderHeaderStop()
								}
							}
						}
						if (subsection.isHit || subsection.isChildHit) {
							renderStr += renderHeaderStop();
						}
					}
				}
				if (section.isHit || section.isChildHit) {
					renderStr += renderHeaderStop();
				}
			}
		}
		if (file.isHit || file.isChildHit) {
			renderStr += renderHeaderStop();
		}
	}

	return renderStr;
}

function clearSearchResult()
{
	var results = $('#searchresults');
	results.empty().append("");
}

function renderSearchResult(resultList)
{
	var results = $('#searchresults');
	var output = "";

	if (resultList.length <= 0) {
		results.html('<p>Sorry, no documents match your query.</p>');
	}

	for (var i = 0; i < renderHeaderMap.length; i++) {
		var fileType = renderHeaderMap[i].type;
		var header = renderHeaderMap[i].header;

		var subsetResultList = resultList.filter(obj => {
			return obj.type == fileType
		});

		if (subsetResultList.length) {
			output += renderTypeStart(header);
			output += renderFileTree(subsetResultList);
			output += renderTypeStop();
		}
	}

	results.append(output);
}

$(document).ready(function() {
	var query = trim(getURLParameter('query'));
	if (query) {
		searchResultList = [];
		curQueryList = tokenzier(query);

		for (var i = 0; i < searchFieldMap.length; i++) {
			var fileType = searchFieldMap[i].type;
			var searchFields = searchFieldMap[i].fields;
			var searchStrategy = searchFieldMap[i].strategy;
			var subsetFileList = fileList.filter(obj => {
				return obj.type == fileType;
			});

			ambaSearch(subsetFileList, query, searchFields,
				idfTerms, searchStrategy).forEach(function(item){
				searchResultList.push(item);
			});
		}

		clearSearchResult();
		renderSearchResult(searchResultList, curQueryList);
	} else {
		var results = $('#searchresults');
		results.html('<p>Sorry, no documents match your query.</p>');
	}

	renderFilter(searchResultList);
});