#ifndef LINKABLETYPE_H
#define LINKABLETYPE_H

namespace duly_gui
{
	template<class T>
	class LinkableType
	{
	public:
		LinkableType() {}
		const T &getValue() const { return m_value; }
		void setValue(T value)
		{
			if (value == m_value)
				return;
			m_value = value;
		}

	private:
		T m_value;
	};

}

#endif // LINKABLETYPE_H
