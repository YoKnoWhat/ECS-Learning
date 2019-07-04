
template<class T>
constexpr std::underlying_type_t<T> CastToUnderlyingType(T value)
{
	return static_cast<std::underlying_type_t<T>>(value);
}
