/*******************************************************************************
 * ambasearch.js
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

var seperator = /[\s\,]+/g;
var maxSegments = 5;
var maxQuoteLength = 30;

/* break document string into tokens, seperate by space and dash */
function tokenzier(str)
{
	return str.toLowerCase().split(seperator).filter(i => i);
}

function findWordIndex(str, word, offset, strategy)
{
	var index = -1;

	if (strategy == "fuzzymatch") {
		index = str.toLowerCase().indexOf(word, offset);
	} else {
		newstr = str.toLowerCase().substring(offset);
		newStrIndex = newstr.search(new RegExp("\\b" + word +"\\b"));
		if (newStrIndex >= 0) {
			index = offset + newStrIndex;
		} else {
			index = newStrIndex;
		}
	}

	return index;
}

function findMatches(text, queryTokens, strategy)
{
	matchIndexList = [];
	matchList = [];

	for (var i = 0; i < queryTokens.length; i++) {
		queryStr = queryTokens[i];

		index = findWordIndex(text, queryStr, 0, strategy);
		while(index >= 0) {
			matchIndexList.push({index: index, length: queryStr.length});
			index = findWordIndex(text, queryStr,
				index + queryStr.length, strategy);
		}
	}
	matchIndexList.sort(function(a, b){return a.index - b.index});

	i = 0;
	fragCount = 0;
	wordList = [];
	while (i < matchIndexList.length && matchList.length < maxSegments) {
		matchIndex = matchIndexList[i].index;
		matchLength = matchIndexList[i].length;
		quoteStart = Math.max(matchIndex - maxQuoteLength, 0);
		quoteEnd = Math.min(matchIndex + matchLength + maxQuoteLength, text.length);
		wordList = [{wordStart: matchIndex, wordEnd: matchIndex + matchLength}]

		while ((i + 1 < matchIndexList.length) &&
			(quoteEnd + maxQuoteLength > matchIndexList[i + 1].index)) {
			i++;
			matchIndex = matchIndexList[i].index;
			matchLength = matchIndexList[i].length;
			quoteEnd = Math.min(matchIndex + matchLength + maxQuoteLength, text.length);
			wordList.push({wordStart: matchIndex, wordEnd: matchIndex + matchLength});
		}

		matchList.push({ quoteStart: quoteStart, quoteEnd: quoteEnd, wordList: wordList });
		i++;
	}

	return matchList
}

function updateMatchInfo(section, queryTokens, fields, strategy)
{
	var isHit = false;

	matchList = findMatches(section.text, queryTokens, strategy);
	section.matchList = matchList;
	if (matchList.length > 0) {
		isHit = true;
	} else {
		for (var i = 0; i < fields.length; i++) {
			field = fields[i];
			if (section[field] && findMatches(section[field],
				queryTokens, strategy).length) {
				isHit = true;
				break;
			}
		}
	}

	section.isHit = isHit;

	return isHit;
}

function getMaxScore(query, idfTerms, dataList)
{
	var maxScore = 0;
	var idfKey = Object.keys(idfTerms).find(key => {return key == query});

	if (idfKey) {
		idfTerm = idfTerms[idfKey];
		for (var i = 0; i < dataList.length; i++) {
			docTerms = dataList[i].terms
			termKey = Object.keys(docTerms).find(key => {return key == query});
			if (termKey) {
				docTerm = docTerms[termKey]
				score = docTerm.freq * idfTerm.idf;
				if (score > maxScore) {
					maxScore = score;
				}
			}
		}
	}

	return maxScore;
}

function nomalizeScore(score, maxScore)
{
	return score/maxScore;
}

function isMatch(str, query, strategy)
{
	var result = false;

	if (strategy == "fuzzymatch") {
		result = str.includes(query);
	} else {
		result = (str == query);
	}

	return result;
}

function isTitleHit(section, query)
{
	var isHit = false;

	if ("title" in section && section.title.toLowerCase().indexOf(query) >= 0) {
		isHit = true;
	} else {
		if ("content" in section) {
			for (var i = 0; i < section.content.length; i++) {
				if (isTitleHit(section.content[i], query)) {
					isHit = true;
					break;
				}
			}
		}
	}

	return isHit
}

function ambaSearch(dataList, queryStr, fields, idfTerms, strategy)
{
	var queryResult = [];

	queryTokens = tokenzier(queryStr);

	/* Calculate scores for current query */
	for (var i = 0; i < queryTokens.length; i++) {
		var idfKey = Object.keys(idfTerms).find(key => {return isMatch(key, queryTokens[i], strategy)});
		if (idfKey) {
			idfTerm = idfTerms[idfKey];
			var maxScore = getMaxScore(queryTokens[i], idfTerms, dataList);
			for (var j = 0; j < dataList.length; j++) {
				docTerms = dataList[j].terms
				termKey = Object.keys(docTerms).find(key => {return isMatch(key, queryTokens[i], strategy)});
				if (termKey) {
					docTerm = docTerms[termKey]
					result = queryResult.find(element => {return element.name == dataList[j].name});
					if (result) {
						result.score += nomalizeScore(docTerm.freq * idfTerm.idf, maxScore);
						result.coord += 1;
					} else {
						dataList[j].score = nomalizeScore(docTerm.freq * idfTerm.idf, maxScore);
						dataList[j].coord = 1;
						queryResult.push(dataList[j]);
					}
				}
			}
		}
	}

	/* Check whether title hits the query */
	queryText = queryStr.toLowerCase()
	for (var i = 0 ; i < queryResult.length; i++) {
		queryResult[i].titleHit = isTitleHit(queryResult[i], queryText) ? 1 : 0;
	}

	/* Rank the query result by number of consecutive matches
	   ex. 'A M B A' > 'A M B' = 'M B A' > 'A M' = 'M B' = 'B A' > rest of inconsecutive matches
	 */
	for (var i = 0; i < queryResult.length; i++) {
		file = queryResult[i];
		fileText = file.alltext ? file.alltext.toLowerCase() : file.text.toLowerCase();
		for (var matchCount = queryTokens.length; matchCount > 0 && !file.tokenMatchCount; matchCount--) {
			for (var tokenIdx = 0; (tokenIdx + matchCount) <= queryTokens.length; tokenIdx++) {
				consecutiveStr = queryTokens.slice(tokenIdx, tokenIdx + matchCount).join(' ')
				if (fileText.indexOf(consecutiveStr) >= 0) {
					file.tokenMatchCount = matchCount
					break;
				}
			}
		}
		if (!file.tokenMatchCount)
			file.tokenMatchCount = 0
	}

	/* Find matches in the fields of a file*/
	for (var i = 0; i < queryResult.length; i++) {
		file = queryResult[i];
		file.isChildHit = false;
		if (file.content) {
			for (var j = 0; j < file.content.length; j++) {
				section = file.content[j];
				section.isChildHit = false;
				if (section.content) {
					for (var k = 0; k < section.content.length; k++) {
						subsection = section.content[k];
						subsection.isChildHit = false;
						if (subsection.content) {
							for (var u = 0; u < subsection.content.length; u++) {
								subsubsection = subsection.content[u];
								if (updateMatchInfo(subsubsection,
									queryTokens, fields, strategy)) {
									subsection.isChildHit = true;
								}
							}
						}
						if (updateMatchInfo(subsection,
							queryTokens, fields, strategy) ||
							subsection.isChildHit) {
							section.isChildHit = true;
						}
					}
				}
				if (updateMatchInfo(section,
					queryTokens, fields, strategy) ||
					section.isChildHit) {
					file.isChildHit = true;
				}
			}
		}
		updateMatchInfo(file, queryTokens, fields, strategy);
	}

	/* Align results in descending order on: title hit, consecutive matches,
	 * inconsecutive matches and scores
	 */
	queryResult.sort(function(a, b){
		return (b.titleHit - a.titleHit) ||
			((b.titleHit == a.titleHit) && (b.tokenMatchCount - a.tokenMatchCount)) ||
			((b.tokenMatchCount == a.tokenMatchCount) && (b.coord - a.coord)) ||
			((b.coord == a.coord) && (b.score - a.score))
	});

	return queryResult
}
