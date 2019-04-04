#include "wnpch.h"
#include "LayerStack.h"

Walnut::LayerStack::LayerStack()
{
}

Walnut::LayerStack::~LayerStack()
{
	for (Layer* layer : mLayers)
		delete layer;
}

void Walnut::LayerStack::PushLayer(Layer * layer)
{
	mLayers.emplace(mLayers.begin() + mLayerInsertIndex, layer);
	mLayerInsertIndex++;
}

void Walnut::LayerStack::PushOverlay(Layer * overlay)
{
	mLayers.emplace_back(overlay);
}

void Walnut::LayerStack::PopLayer(Layer * layer)
{
	auto it = std::find(mLayers.begin(), mLayers.end(), layer);
	if (it != mLayers.end())
	{
		mLayers.erase(it);
		mLayerInsertIndex--;
	}
}

void Walnut::LayerStack::PopOverlay(Layer * overlay)
{
	auto it = std::find(mLayers.begin(), mLayers.end(), overlay);
	if (it != mLayers.end())
		mLayers.erase(it);
}
