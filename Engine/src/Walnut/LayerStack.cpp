#include "wnpch.h"
#include "LayerStack.h"

Walnut::LayerStack::LayerStack()
{
	mLayerInsert = mLayers.begin();
}

Walnut::LayerStack::~LayerStack()
{
	for (Layer* layer : mLayers)
		delete layer;
}

void Walnut::LayerStack::PushLayer(Layer * layer)
{
	mLayerInsert = mLayers.emplace(mLayerInsert, layer);
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
		mLayerInsert--;
	}
}

void Walnut::LayerStack::PopOverlay(Layer * overlay)
{
	auto it = std::find(mLayers.begin(), mLayers.end(), overlay);
	if (it != mLayers.end())
		mLayers.erase(it);
}
