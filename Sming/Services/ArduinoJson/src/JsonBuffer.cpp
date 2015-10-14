// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include "../include/ArduinoJson/JsonBuffer.hpp"

#include "../include/ArduinoJson/Internals/JsonParser.hpp"
#include "../include/ArduinoJson/JsonArray.hpp"
#include "../include/ArduinoJson/JsonObject.hpp"
#include "../include/ArduinoJson/Internals/JsonStringStorage.hpp"

using namespace ArduinoJson;
using namespace ArduinoJson::Internals;

JsonStringStorage JsonStringStorage::_invalid(NULL);

JsonArray &JsonBuffer::createArray()
{
	JsonArray *ptr = new (this) JsonArray(this);
	if (ptr)
	{
		allocs.add(ptr);
	}
	return ptr ? *ptr : JsonArray::invalid();
}

JsonObject &JsonBuffer::createObject()
{
	JsonObject *ptr = new (this) JsonObject(this);
	if (ptr)
	{
		allocs.add(ptr);
	}
	return ptr ? *ptr : JsonObject::invalid();
}

JsonBuffer::~JsonBuffer()
{
	for (int i = 0; i < allocs.size(); ++i)
	{
		delete allocs[i];
	}
}
JsonArray &JsonBuffer::parseArray(char *json, uint8_t nestingLimit)
{
	JsonParser parser(this, json, nestingLimit);
	return parser.parseArray();
}

JsonObject &JsonBuffer::parseObject(char *json, uint8_t nestingLimit)
{
	JsonParser parser(this, json, nestingLimit);
	return parser.parseObject();
}

JsonStringStorage& ArduinoJson::JsonBuffer::createStringStorage(
		const String& text)
{
	JsonStringStorage *ptr = new (this) JsonStringStorage(text);
	if (ptr)
	{
		allocs.add(ptr);
	}
	return ptr ? *ptr : JsonStringStorage::invalid();
}
