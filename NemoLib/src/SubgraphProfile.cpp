/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 /*
  * File:   SubgraphProfile.cpp
  * Author: Wooyoung
  *
  * Created on October 29, 2017, 3:05 PM
  */

#include "SubgraphProfile.hpp"
#include "Subgraph.hpp"
#include "NautyLink.hpp"
#include "Utility.hpp"

using std::cout;
using std::ostream;
using std::vector;
using std::unordered_map;

//need the subgraphsize to compute subgraphcount for each label

/* Add subgraphs using label
 * Just to check, we will implement without labeling yet
 */
void SubgraphProfile::add(Subgraph& currentSubgraph, NautyLink& nautylink)
{
	// first, get the label
	std::string label = nautylink.nautylabel_helper(currentSubgraph);

	// get the current nodes
	vector<vertex>& nodes = currentSubgraph.getNodes();

	// if the key already exists, then update
	if (labelVertexFreqMapMap.count(label) == 0)
	{
		labelVertexFreqMapMap[label] = std::vector<uint64_t>(graphsize, 0);
	}

	// update the map
	for (int i = 0; static_cast<std::size_t>(i) < currentSubgraph.getSize(); i++)
	{
		labelVertexFreqMapMap[label][nodes[i]] += 1;
	}
}


unordered_map<std::string, uint64_t> SubgraphProfile::getlabelFreqMap(int subgraphsize)
{
	unordered_map <std::string, uint64_t> labelFreqMap;

	for (auto& p : labelVertexFreqMapMap)
	{
		uint64_t countLabel = get_vector_sum(p.second.begin(), p.second.end(), uint64_t{0});
		labelFreqMap[p.first] = countLabel / subgraphsize;
	}
	return labelFreqMap;
}

unordered_map <std::string, double> SubgraphProfile::getRelativeFrequencies() const
{
	unordered_map<std::string, double> result(labelVertexFreqMapMap.size());
	auto totalcount = getTotalSubgaphCount();

	for (auto& p : labelVertexFreqMapMap)
	{
		auto countLabel = get_vector_sum(p.second.begin(), p.second.end(), uint64_t{0});
		result[p.first] = static_cast<double>(countLabel) / static_cast<double>(totalcount);
	}

	return result;
}
