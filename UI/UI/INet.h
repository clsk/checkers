#pragma once
#include "Messages.pb.h"
public interface class INet
{
	void send(const move& message);
};