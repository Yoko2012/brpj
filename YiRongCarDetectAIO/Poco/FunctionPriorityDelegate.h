//
// FunctionPriorityDelegate.h
//
// $Id: //poco/1.4/Foundation/include/Poco/FunctionPriorityDelegate.h#5 $
//
// Library: Foundation
// Package: Events
// Module:  FunctionPriorityDelegate
//
// Implementation of the FunctionPriorityDelegate template.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_FunctionPriorityDelegate_INCLUDED
#define Foundation_FunctionPriorityDelegate_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/AbstractPriorityDelegate.h"
#include "Poco/Mutex.h"


namespace Poco {


template <class TArgs, bool useSender = true, bool senderIsConst = true> 
class FunctionPriorityDelegate: public AbstractPriorityDelegate<TArgs>
	/// Wraps a freestanding function or static member function 
	/// for use as a PriorityDelegate.
{
public:
	typedef void (*NotifyMethod)(const void*, TArgs&);

	FunctionPriorityDelegate(NotifyMethod method, int prio):
		AbstractPriorityDelegate<TArgs>(prio),
		_receiverMethod(method)
	{
	}
	
	FunctionPriorityDelegate(const FunctionPriorityDelegate& delegate):
		AbstractPriorityDelegate<TArgs>(delegate),
		_receiverMethod(delegate._receiverMethod)
	{
	}
	
	FunctionPriorityDelegate& operator = (const FunctionPriorityDelegate& delegate)
	{
		if (&delegate != this)
		{
			this->_pTarget        = delegate._pTarget;
			this->_receiverMethod = delegate._receiverMethod;
			this->_priority       = delegate._priority;
		}
		return *this;
	}

	~FunctionPriorityDelegate()
	{
	}

	bool notify(const void* sender, TArgs& arguments)
	{
		Mutex::ScopedLock lock(_mutex);
		if (_receiverMethod)
		{
			(*_receiverMethod)(sender, arguments);
			return true;
		}
		else return false;
	}

	bool equals(const AbstractDelegate<TArgs>& other) const
	{
		const FunctionPriorityDelegate* pOtherDelegate = dynamic_cast<const FunctionPriorityDelegate*>(other.unwrap());
		return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverMethod == pOtherDelegate->_receiverMethod;
	}

	AbstractDelegate<TArgs>* clone() const
	{
		return new FunctionPriorityDelegate(*this);
	}

	void disable()
	{
		Mutex::ScopedLock lock(_mutex);
		_receiverMethod = 0;
	}

protected:
	NotifyMethod _receiverMethod;
	Mutex _mutex;

private:
	FunctionPriorityDelegate();
};


template <class TArgs> 
class FunctionPriorityDelegate<TArgs, true, false>: public AbstractPriorityDelegate<TArgs>
{
public:
	typedef void (*NotifyMethod)(void*, TArgs&);

	FunctionPriorityDelegate(NotifyMethod method, int prio):
		AbstractPriorityDelegate<TArgs>(prio),
		_receiverMethod(method)
	{
	}
	
	FunctionPriorityDelegate(const FunctionPriorityDelegate& delegate):
		AbstractPriorityDelegate<TArgs>(delegate),
		_receiverMethod(delegate._receiverMethod)
	{
	}
	
	FunctionPriorityDelegate& operator = (const FunctionPriorityDelegate& delegate)
	{
		if (&delegate != this)
		{
			this->_pTarget        = delegate._pTarget;
			this->_receiverMethod = delegate._receiverMethod;
			this->_priority       = delegate._priority;
		}
		return *this;
	}

	~FunctionPriorityDelegate()
	{
	}

	bool notify(const void* sender, TArgs& arguments)
	{
		Mutex::ScopedLock lock(_mutex);
		if (_receiverMethod)
		{
			(*_receiverMethod)(const_cast<void*>(sender), arguments);
			return true;
		}
		else return false;
	}

	bool equals(const AbstractDelegate<TArgs>& other) const
	{
		const FunctionPriorityDelegate* pOtherDelegate = dynamic_cast<const FunctionPriorityDelegate*>(other.unwrap());
		return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverMethod == pOtherDelegate->_receiverMethod;
	}

	AbstractDelegate<TArgs>* clone() const
	{
		return new FunctionPriorityDelegate(*this);
	}

	void disable()
	{
		Mutex::ScopedLock lock(_mutex);
		_receiverMethod = 0;
	}

protected:
	NotifyMethod _receiverMethod;
	Mutex _mutex;

private:
	FunctionPriorityDelegate();
};


template <class TArgs> 
class FunctionPriorityDelegate<TArgs, false>: public AbstractPriorityDelegate<TArgs>
{
public:
	typedef void (*NotifyMethod)(TArgs&);

	FunctionPriorityDelegate(NotifyMethod method, int prio):
		AbstractPriorityDelegate<TArgs>(prio),
		_receiverMethod(method)
	{
	}
	
	FunctionPriorityDelegate(const FunctionPriorityDelegate& delegate):
		AbstractPriorityDelegate<TArgs>(delegate),
		_receiverMethod(delegate._receiverMethod)
	{
	}
	
	FunctionPriorityDelegate& operator = (const FunctionPriorityDelegate& delegate)
	{
		if (&delegate != this)
		{
			this->_pTarget        = delegate._pTarget;
			this->_receiverMethod = delegate._receiverMethod;
			this->_priority       = delegate._priority;
		}
		return *this;
	}

	~FunctionPriorityDelegate()
	{
	}

	bool notify(const void* sender, TArgs& arguments)
	{
		Mutex::ScopedLock lock(_mutex);
		if (_receiverMethod)
		{
			(*_receiverMethod)(arguments);
			return true;
		}
		else return false;
	}

	bool equals(const AbstractDelegate<TArgs>& other) const
	{
		const FunctionPriorityDelegate* pOtherDelegate = dynamic_cast<const FunctionPriorityDelegate*>(other.unwrap());
		return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverMethod == pOtherDelegate->_receiverMethod;
	}

	AbstractDelegate<TArgs>* clone() const
	{
		return new FunctionPriorityDelegate(*this);
	}

	void disable()
	{
		Mutex::ScopedLock lock(_mutex);
		_receiverMethod = 0;
	}

protected:
	NotifyMethod _receiverMethod;
	Mutex _mutex;

private:
	FunctionPriorityDelegate();
};


} // namespace Poco


#endif // Foundation_FunctionPriorityDelegate_INCLUDED
