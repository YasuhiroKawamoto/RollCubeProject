//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @File  ModelManager.cpp
//!
//! @Brief  ModelManagerクラスのヘッダファイル
//!
//! @Date   2017/07/30
//!
//! @Author Y.Kawamoto
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

#include <map>

#include <wrl/client.h>
#include <d3d11_1.h>
#include <Model.h>
#include <Effects.h>

class ModelManager
{
private:
	static ModelManager* m_instance;
	//　ファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	std::map <std::wstring, std::unique_ptr<DirectX::Model >> m_models;
public:
	~ModelManager() {}
	std::unique_ptr<DirectX::Model> GetModel(const std::wstring& key);

private:
	ModelManager();
public:
	static ModelManager* GetInstance();

};
