<?xml version="1.0"?><doc>
<members>
<member name="T:Poco.Bugcheck" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="35">
This class provides some static methods that are
used by the
poco_assert_dbg(), poco_assert(), poco_check_ptr(), 
poco_bugcheck() and poco_unexpected() macros. 
You should not invoke these methods
directly. Use the macros instead, as they
automatically provide useful context information.
</member>
<member name="M:Poco.Bugcheck.nullPointer(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="45">
An assertion failed. Break into the debugger, if
possible, then throw an AssertionViolationException.
</member>
<member name="M:Poco.Bugcheck.bugcheck(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="49">
An null pointer was encountered. Break into the debugger, if
possible, then throw an NullPointerException.
</member>
<member name="M:Poco.Bugcheck.bugcheck(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="53">
An internal error was encountered. Break into the debugger, if
possible, then throw an BugcheckException.
</member>
<member name="M:Poco.Bugcheck.unexpected(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="57">
An internal error was encountered. Break into the debugger, if
possible, then throw an BugcheckException.
</member>
<member name="M:Poco.Bugcheck.debugger(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="61">
An exception was caught in a destructor. Break into debugger,
if possible and report exception. Must only be called from
within a catch () block as it rethrows the exception to
determine its class.
</member>
<member name="M:Poco.Bugcheck.debugger(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="67">
An internal error was encountered. Break into the debugger, if
possible.
</member>
<member name="M:Poco.Bugcheck.what(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int32,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\bugcheck.h" line="71">
An internal error was encountered. Break into the debugger, if
possible.
</member>
<member name="M:Poco.Net.uninitializeNetwork" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\net.h" line="77">
Initialize the network subsystem.
(Windows only, no-op elsewhere)
</member>
<member name="T:Poco.Net.AddressFamily" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socketdefs.h" line="361">
AddressFamily::Family replaces the previously used IPAddress::Family
enumeration and is now used for IPAddress::Family and SocketAddress::Family.
</member>
<member name="T:Poco.Net.AddressFamily.Family" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socketdefs.h" line="365">
Possible address families for socket addresses.
</member>
<member name="F:IPv6" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socketdefs.h" line="368">
IPv4 address family.
</member>
<member name="M:Poco.Exception.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="31">
This is the base class for all exceptions defined
in the Poco class library.
</member>
<member name="M:Poco.Exception.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="36">
Creates an exception.
</member>
<member name="M:Poco.Exception.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Exception!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="39">
Creates an exception.
</member>
<member name="M:Poco.Exception.#ctor(Poco.Exception!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="42">
Creates an exception and stores a clone
of the nested exception.
</member>
<member name="M:Poco.Exception.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="46">
Copy constructor.
</member>
<member name="M:Poco.Exception.op_Assign(Poco.Exception!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="49">
Destroys the exception and deletes the nested exception.
</member>
<member name="M:Poco.Exception.name" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="52">
Assignment operator.
</member>
<member name="M:Poco.Exception.className" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="55">
Returns a static string describing the exception.
</member>
<member name="M:Poco.Exception.what" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="58">
Returns the name of the exception class.
</member>
<member name="M:Poco.Exception.nested" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="61">
Returns a static string describing the exception.

Same as name(), but for compatibility with std::exception.
</member>
<member name="M:Poco.Exception.message" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="66">
Returns a pointer to the nested exception, or
null if no nested exception exists.
</member>
<member name="M:Poco.Exception.code" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="70">
Returns the message text.
</member>
<member name="M:Poco.Exception.displayText" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="73">
Returns the exception code if defined.
</member>
<member name="M:Poco.Exception.clone" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="76">
Returns a string consisting of the
message name and the message text.
</member>
<member name="M:Poco.Exception.rethrow" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="80">
Creates an exact copy of the exception.

The copy can later be thrown again by
invoking rethrow() on it.
</member>
<member name="M:Poco.Exception.#ctor(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="86">
(Re)Throws the exception.

This is useful for temporarily storing a
copy of an exception (see clone()), then
throwing it again.
</member>
<member name="M:Poco.Exception.message(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="94">
Standard constructor.
</member>
<member name="M:Poco.Exception.extendedMessage(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="97">
Sets the message for the exception.
</member>
<member name="F:Poco.Exception._msg" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\exception.h" line="100">
Sets the extended message for the exception.
</member>
<!-- Discarding badly formed XML document comment for member 'T:Poco.Net.IPAddress'. -->
<member name="M:Poco.Net.IPAddress.#ctor(Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="71">
Creates a wildcard (zero) IPv4 IPAddress.
</member>
<member name="M:Poco.Net.IPAddress.#ctor(Poco.Net.AddressFamily.Family)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="74">
Creates an IPAddress by copying another one.
</member>
<member name="M:Poco.Net.IPAddress.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="77">
Creates a wildcard (zero) IPAddress for the
given address family.
</member>
<member name="M:Poco.Net.IPAddress.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.AddressFamily.Family)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="81">
Creates an IPAddress from the string containing
an IP address in presentation format (dotted decimal
for IPv4, hex string for IPv6).

Depending on the format of addr, either an IPv4 or
an IPv6 address is created.

See toString() for details on the supported formats.

Throws an InvalidAddressException if the address cannot be parsed.
</member>
<member name="M:Poco.Net.IPAddress.#ctor(System.Void!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="93">
Creates an IPAddress from the string containing
an IP address in presentation format (dotted decimal
for IPv4, hex string for IPv6).
</member>
<member name="M:Poco.Net.IPAddress.#ctor(System.Void!System.Runtime.CompilerServices.IsConst*,System.Int32,System.UInt32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="98">
Creates an IPAddress from a native internet address.
A pointer to a in_addr or a in6_addr structure may be 
passed.
</member>
<member name="M:Poco.Net.IPAddress.#ctor(System.UInt32,Poco.Net.AddressFamily.Family)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="103">
Creates an IPAddress from a native internet address.
A pointer to a in_addr or a in6_addr structure may be 
passed. Additionally, for an IPv6 address, a scope ID
may be specified. The scope ID will be ignored if an IPv4
address is specified.
</member>
<member name="M:Poco.Net.IPAddress.#ctor(_SOCKET_ADDRESS!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="110">
Creates an IPAddress mask with the given length of prefix.
</member>
<member name="T:sockaddr" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="114">
Creates an IPAddress from Windows SOCKET_ADDRESS structure.
</member>
<member name="M:Poco.Net.IPAddress.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="118">
Same for struct sock_addr on POSIX.
</member>
<member name="M:Poco.Net.IPAddress.op_Assign(Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="122">
Destroys the IPAddress.
</member>
<member name="M:Poco.Net.IPAddress.family" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="125">
Assigns an IPAddress.
</member>
<member name="M:Poco.Net.IPAddress.scope" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="128">
Returns the address family (IPv4 or IPv6) of the address.
</member>
<member name="M:Poco.Net.IPAddress.toString" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="131">
Returns the IPv6 scope identifier of the address. Returns 0 if
the address is an IPv4 address, or the address is an
IPv6 address but does not have a scope identifier.
</member>
<member name="M:Poco.Net.IPAddress.isWildcard" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="136">
Returns a string containing a representation of the address
in presentation format.

For IPv4 addresses the result will be in dotted-decimal
(d.d.d.d) notation.

Textual representation of IPv6 address is one of the following forms:

The preferred form is x:x:x:x:x:x:x:x, where the 'x's are the hexadecimal 
values of the eight 16-bit pieces of the address. This is the full form.
Example: 1080:0:0:0:8:600:200A:425C

It is not necessary to write the leading zeros in an individual field. 
However, there must be at least one numeral in every field, except as described below.

It is common for IPv6 addresses to contain long strings of zero bits. 
In order to make writing addresses containing zero bits easier, a special syntax is 
available to compress the zeros. The use of "::" indicates multiple groups of 16-bits of zeros. 
The "::" can only appear once in an address. The "::" can also be used to compress the leading 
and/or trailing zeros in an address. Example: 1080::8:600:200A:425C

For dealing with IPv4 compatible addresses in a mixed environment,
a special syntax is available: x:x:x:x:x:x:d.d.d.d, where the 'x's are the 
hexadecimal values of the six high-order 16-bit pieces of the address, 
and the 'd's are the decimal values of the four low-order 8-bit pieces of the 
standard IPv4 representation address. Example: ::FFFF:192.168.1.120

If an IPv6 address contains a non-zero scope identifier, it is added
to the string, delimited by a percent character. On Windows platforms,
the numeric value (which specifies an interface index) is directly
appended. On Unix platforms, the name of the interface corresponding
to the index (interpretation of the scope identifier) is added.
</member>
<member name="M:Poco.Net.IPAddress.isBroadcast" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="170">
Returns true iff the address is a wildcard (all zero)
address.
</member>
<member name="M:Poco.Net.IPAddress.isLoopback" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="174">
Returns true iff the address is a broadcast address.

Only IPv4 addresses can be broadcast addresses. In a broadcast
address, all bits are one.

For an IPv6 address, returns always false.
</member>
<member name="M:Poco.Net.IPAddress.isMulticast" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="182">
Returns true iff the address is a loopback address.

For IPv4, the loopback address is 127.0.0.1.

For IPv6, the loopback address is ::1.
</member>
<member name="M:Poco.Net.IPAddress.isUnicast" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="189">
Returns true iff the address is a multicast address.

IPv4 multicast addresses are in the
224.0.0.0 to 239.255.255.255 range
(the first four bits have the value 1110).

IPv6 multicast addresses are in the
FFxx:x:x:x:x:x:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.isLinkLocal" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="199">
Returns true iff the address is a unicast address.

An address is unicast if it is neither a wildcard,
broadcast or multicast address.
</member>
<member name="M:Poco.Net.IPAddress.isSiteLocal" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="205">
Returns true iff the address is a link local unicast address.

IPv4 link local addresses are in the 169.254.0.0/16 range,
according to RFC 3927.

IPv6 link local addresses have 1111 1110 10 as the first
10 bits, followed by 54 zeros.
</member>
<member name="M:Poco.Net.IPAddress.isIPv4Compatible" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="214">
Returns true iff the address is a site local unicast address.

IPv4 site local addresses are in on of the 10.0.0.0/24,
192.168.0.0/16 or 172.16.0.0 to 172.31.255.255 ranges.

Originally, IPv6 site-local addresses had FEC0/10 (1111 1110 11) 
prefix (RFC 4291), followed by 38 zeros. Interfaces using  
this mask are supported, but obsolete; RFC 4193 prescribes
fc00::/7 (1111 110) as local unicast prefix.
</member>
<member name="M:Poco.Net.IPAddress.isIPv4Mapped" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="225">
Returns true iff the address is IPv4 compatible.

For IPv4 addresses, this is always true.

For IPv6, the address must be in the ::x:x range (the
first 96 bits are zero).
</member>
<member name="M:Poco.Net.IPAddress.isWellKnownMC" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="233">
Returns true iff the address is an IPv4 mapped IPv6 address.

For IPv4 addresses, this is always true.

For IPv6, the address must be in the ::FFFF:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.isNodeLocalMC" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="240">
Returns true iff the address is a well-known multicast address.

For IPv4, well-known multicast addresses are in the 
224.0.0.0/8 range.

For IPv6, well-known multicast addresses are in the 
FF0x:x:x:x:x:x:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.isLinkLocalMC" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="249">
Returns true iff the address is a node-local multicast address.

IPv4 does not support node-local addresses, thus the result is
always false for an IPv4 address.

For IPv6, node-local multicast addresses are in the
FFx1:x:x:x:x:x:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.isSiteLocalMC" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="258">
Returns true iff the address is a link-local multicast address.

For IPv4, link-local multicast addresses are in the
224.0.0.0/24 range. Note that this overlaps with the range for well-known
multicast addresses.

For IPv6, link-local multicast addresses are in the
FFx2:x:x:x:x:x:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.isOrgLocalMC" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="268">
Returns true iff the address is a site-local multicast address.

For IPv4, site local multicast addresses are in the
239.255.0.0/16 range.

For IPv6, site-local multicast addresses are in the
FFx5:x:x:x:x:x:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.isGlobalMC" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="277">
Returns true iff the address is a organization-local multicast address.

For IPv4, organization-local multicast addresses are in the
239.192.0.0/16 range.

For IPv6, organization-local multicast addresses are in the
FFx8:x:x:x:x:x:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.op_Equality(Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="286">
Returns true iff the address is a global multicast address.

For IPv4, global multicast addresses are in the 
224.0.1.0 to 238.255.255.255 range.

For IPv6, global multicast addresses are in the
FFxF:x:x:x:x:x:x:x range.
</member>
<member name="M:Poco.Net.IPAddress.addr" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="306">
Returns the length in bytes of the internal socket address structure.	
</member>
<member name="M:Poco.Net.IPAddress.af" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="309">
Returns the internal address structure.
</member>
<member name="M:Poco.Net.IPAddress.prefixLength" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="312">
Returns the address family (AF_INET or AF_INET6) of the address.
</member>
<member name="M:Poco.Net.IPAddress.mask(Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="315">
Returns the prefix length.
</member>
<!-- Discarding badly formed XML document comment for member 'M:Poco.Net.IPAddress.mask(Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)'. -->
<!-- Discarding badly formed XML document comment for member 'M:Poco.Net.IPAddress.parse(std.basic_string<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte>>!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)'. -->
<member name="M:Poco.Net.IPAddress.tryParse(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.IPAddress*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="330">
Creates an IPAddress from the string containing
an IP address in presentation format (dotted decimal
for IPv4, hex string for IPv6).

Depending on the format of addr, either an IPv4 or
an IPv6 address is created.

See toString() for details on the supported formats.

Throws an InvalidAddressException if the address cannot be parsed.
</member>
<member name="M:Poco.Net.IPAddress.wildcard(Poco.Net.AddressFamily.Family)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="342">
Tries to interpret the given address string as an
IP address in presentation format (dotted decimal
for IPv4, hex string for IPv6).

Returns true and stores the IPAddress in result if the
string contains a valid address.

Returns false and leaves result unchanged otherwise.
</member>
<member name="M:Poco.Net.IPAddress.broadcast" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="352">
Returns a wildcard IPv4 or IPv6 address (0.0.0.0).
</member>
<member name="F:MAX_ADDRESS_LENGTH" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\ipaddress.h" line="365">
Maximum length in bytes of a socket address.
</member>
<member name="T:Poco.Net.SocketAddress" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="40">
This class represents an internet (IP) endpoint/socket
address. The address can belong either to the
IPv4 or the IPv6 address family and consists of a
host address and a port number.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(Poco.Net.AddressFamily.Family)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="59">
Creates a wildcard (all zero) IPv4 SocketAddress.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="62">
Creates a SocketAddress with unspecified (wildcard) IP address 
of the given family.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="66">
Creates a SocketAddress from an IP address and given port number.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(Poco.Net.AddressFamily.Family,System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="69">
Creates a SocketAddress with unspecified (wildcard) IP address 
and given port number.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="73">
Creates a SocketAddress with unspecified (wildcard) IP address 
of the given family, and given port number.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(Poco.Net.AddressFamily.Family,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="77">
Creates a SocketAddress from an IP address and given port number.

The IP address must either be a domain name, or it must
be in dotted decimal (IPv4) or hex string (IPv6) format.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="83">
Creates a SocketAddress from an IP address and given port number.

The IP address must either be a domain name, or it must
be in dotted decimal (IPv4) or hex string (IPv6) format.

If a domain name is given in hostAddress, it is resolved and the address
matching the given family is used. If no address matching the given family
is found, or the IP address given in hostAddress does not match the given
family, an AddressFamilyMismatchException is thrown.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(Poco.Net.AddressFamily.Family,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="94">
Creates a SocketAddress from an IP address and the
service name or port number.

The IP address must either be a domain name, or it must
be in dotted decimal (IPv4) or hex string (IPv6) format.

The given port must either be a decimal port number, or
a service name.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="104">
Creates a SocketAddress from an IP address and the
service name or port number.

The IP address must either be a domain name, or it must
be in dotted decimal (IPv4) or hex string (IPv6) format.

The given port must either be a decimal port number, or
a service name.

If a domain name is given in hostAddress, it is resolved and the address
matching the given family is used. If no address matching the given family
is found, or the IP address given in hostAddress does not match the given
family, an AddressFamilyMismatchException is thrown.
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(Poco.Net.AddressFamily.Family,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="119">
Creates a SocketAddress from an IP address or host name and the
port number/service name. Host name/address and port number must
be separated by a colon. In case of an IPv6 address,
the address part must be enclosed in brackets.

Examples:
    192.168.1.10:80
    [::ffff:192.168.1.120]:2040
    www.appinf.com:8080

On POSIX platforms supporting UNIX_LOCAL sockets, hostAndPort
can also be the absolute path of a local socket, starting with a 
slash, e.g. "/tmp/local.socket".
</member>
<member name="M:Poco.Net.SocketAddress.#ctor(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="134">
Creates a SocketAddress of the given family from a
string representation of the address, which is
either an IP address and port number, separated by
a colon for IPv4 or IPv6 addresses, or a path for
UNIX_LOCAL sockets.
</member>
<member name="T:sockaddr" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="141">
Creates a SocketAddress by copying another one.
</member>
<member name="M:Poco.Net.SocketAddress.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="144">
Creates a SocketAddress from a native socket address.
</member>
<member name="M:Poco.Net.SocketAddress.op_Assign(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="147">
Destroys the SocketAddress.
</member>
<member name="M:Poco.Net.SocketAddress.host" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="150">
Assigns another SocketAddress.
</member>
<member name="M:Poco.Net.SocketAddress.port" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="153">
Returns the host IP address.
</member>
<member name="M:Poco.Net.SocketAddress.length" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="156">
Returns the port number.
</member>
<member name="T:sockaddr" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="159">
Returns the length of the internal native socket address.
</member>
<member name="M:Poco.Net.SocketAddress.af" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="162">
Returns a pointer to the internal native socket address.
</member>
<member name="M:Poco.Net.SocketAddress.toString" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="165">
Returns the address family (AF_INET or AF_INET6) of the address.
</member>
<member name="M:Poco.Net.SocketAddress.family" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="168">
Returns a string representation of the address.
</member>
<member name="M:Poco.Net.SocketAddress.op_LessThan(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="171">
Returns the address family of the host's address.
</member>
<member name="F:MAX_ADDRESS_LENGTH" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socketaddress.h" line="187">
Maximum length in bytes of a socket address.
</member>
<member name="T:Poco.Mutex.MutexType" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="45">
A Mutex (mutual exclusion) is a synchronization 
mechanism used to control access to a shared resource
in a concurrent (multithreaded) scenario.
Using the ScopedLock class is the preferred way to automatically
lock and unlock a mutex.
The type of a mutex.
</member>
<member name="M:Poco.Mutex.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="62">
Creates the Mutex.
</member>
<member name="M:Poco.Mutex.lock" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="65">
Destroys the Mutex.
</member>
<member name="M:Poco.Mutex.lock(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="68">
Locks the mutex. Blocks if the mutex
is held by another thread.
</member>
<member name="M:Poco.Mutex.tryLock" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="72">
Locks the mutex. Blocks up to the given number of milliseconds
if the mutex is held by another thread. Throws a TimeoutException
if the mutex can not be locked within the given timeout.

Performance Note: On most platforms (including Windows), this member function is 
implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
On POSIX platforms that support pthread_mutex_timedlock(), this is used.
</member>
<member name="M:Poco.Mutex.tryLock(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="81">
Tries to lock the mutex. Returns false immediately
if the mutex is already held by another thread.
Returns true if the mutex was successfully locked.
</member>
<member name="M:Poco.Mutex.unlock" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="86">
Locks the mutex. Blocks up to the given number of milliseconds
if the mutex is held by another thread.
Returns true if the mutex was successfully locked.

Performance Note: On most platforms (including Windows), this member function is 
implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
On POSIX platforms that support pthread_mutex_timedlock(), this is used.
</member>
<member name="M:Poco.Mutex.#ctor(Poco.Mutex!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="95">
Unlocks the mutex so that it can be acquired by
other threads.
</member>
<member name="D:Poco.FastMutex.ScopedLock" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="105">
A FastMutex (mutual exclusion) is similar to a Mutex.
Locking a FastMutex is guaranteed to be at least as
fast as locking a Mutex.  However, a FastMutex is not
guaranteed to be either recursive or non-recursive.
It is best suited to thread safe components like pools,
caches and queues where locking is internal to the component.
Using the ScopedLock class is the preferred way to automatically
lock and unlock a mutex.
</member>
<member name="M:Poco.FastMutex.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="118">
creates the Mutex.
</member>
<member name="M:Poco.FastMutex.lock" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="121">
destroys the Mutex.
</member>
<member name="M:Poco.FastMutex.lock(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="124">
Locks the mutex. Blocks if the mutex
is held by another thread.
</member>
<member name="M:Poco.FastMutex.tryLock" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="128">
Locks the mutex. Blocks up to the given number of milliseconds
if the mutex is held by another thread. Throws a TimeoutException
if the mutex can not be locked within the given timeout.

Performance Note: On most platforms (including Windows), this member function is 
implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
On POSIX platforms that support pthread_mutex_timedlock(), this is used.
</member>
<member name="M:Poco.FastMutex.tryLock(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="137">
Tries to lock the mutex. Returns false immediately
if the mutex is already held by another thread.
Returns true if the mutex was successfully locked.
</member>
<member name="M:Poco.FastMutex.unlock" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="142">
Locks the mutex. Blocks up to the given number of milliseconds
if the mutex is held by another thread.
Returns true if the mutex was successfully locked.

Performance Note: On most platforms (including Windows), this member function is 
implemented using a loop calling (the equivalent of) tryLock() and Thread::sleep().
On POSIX platforms that support pthread_mutex_timedlock(), this is used.
</member>
<member name="M:Poco.FastMutex.#ctor(Poco.FastMutex!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="151">
Unlocks the mutex so that it can be acquired by
other threads.
</member>
<member name="T:Poco.NullMutex" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="161">
A NullMutex is an empty mutex implementation
which performs no locking at all. Useful in policy driven design
where the type of mutex used can be now a template parameter allowing the user to switch
between thread-safe and not thread-safe depending on his need
Works with the ScopedLock class
</member>
<member name="M:Poco.NullMutex.#ctor" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="171">
Creates the NullMutex.
</member>
<member name="M:Poco.NullMutex.Dispose" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="176">
Destroys the NullMutex.
</member>
<member name="M:Poco.NullMutex.lock" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="181">
Does nothing.
</member>
<member name="M:Poco.NullMutex.lock(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="186">
Does nothing.
</member>
<member name="M:Poco.NullMutex.tryLock" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="191">
Does nothing and always returns true.
</member>
<member name="M:Poco.NullMutex.tryLock(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="197">
Does nothing and always returns true.
</member>
<member name="M:Poco.NullMutex.unlock" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\mutex.h" line="203">
Does nothing.
</member>
<member name="T:Poco.AtomicCounter" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="55">
This class implements a simple counter, which
provides atomic operations that are safe to
use in a multithreaded environment.

Typical usage of AtomicCounter is for implementing
reference counting and similar things.

On some platforms, the implementation of AtomicCounter
is based on atomic primitives specific to the platform
(such as InterlockedIncrement, etc. on Windows), and
thus very efficient. On platforms that do not support
atomic primitives, operations are guarded by a FastMutex.

The following platforms currently have atomic
primitives:
  - Windows
  - Mac OS X
  - GCC 4.1+ (Intel platforms only)
</member>
<member name="M:Poco.AtomicCounter.#ctor(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="78">
Creates a new AtomicCounter and initializes it to zero.
</member>
<member name="M:Poco.AtomicCounter.#ctor(Poco.AtomicCounter!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="81">
Creates a new AtomicCounter and initializes it with
the given value.
</member>
<member name="M:Poco.AtomicCounter.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="85">
Creates the counter by copying another one.
</member>
<member name="M:Poco.AtomicCounter.op_Assign(Poco.AtomicCounter!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="88">
Destroys the AtomicCounter.
</member>
<member name="M:Poco.AtomicCounter.op_Assign(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="91">
Assigns the value of another AtomicCounter.
</member>
<member name="M:Poco.AtomicCounter.op_Implicit~System.Int32" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="94">
Assigns a value to the counter.
</member>
<member name="M:Poco.AtomicCounter.value" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="97">
Returns the value of the counter.
</member>
<member name="M:Poco.AtomicCounter.op_Increment" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="100">
Returns the value of the counter.
</member>
<member name="M:Poco.AtomicCounter.op_Increment(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="103">
Increments the counter and returns the result.
</member>
<member name="M:Poco.AtomicCounter.op_Decrement" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="106">
Increments the counter and returns the previous value.
</member>
<member name="M:Poco.AtomicCounter.op_Decrement(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="109">
Decrements the counter and returns the result.
</member>
<member name="M:Poco.AtomicCounter.op_LogicalNot" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="112">
Decrements the counter and returns the previous value.
</member>
<member name="D:Poco.AtomicCounter.ImplType" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\atomiccounter.h" line="115">
Returns true if the counter is zero, false otherwise.
</member>
<member name="T:Poco.RefCountedObject" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\refcountedobject.h" line="31">
A base class for objects that employ
reference counting based garbage collection.

Reference-counted objects inhibit construction
by copying and assignment.
</member>
<member name="M:Poco.RefCountedObject.duplicate" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\refcountedobject.h" line="39">
Creates the RefCountedObject.
The initial reference count is one.
</member>
<member name="M:Poco.RefCountedObject.release" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\refcountedobject.h" line="43">
Increments the object's reference count.
</member>
<member name="M:Poco.RefCountedObject.referenceCount" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\refcountedobject.h" line="46">
Decrements the object's reference count
and deletes the object if the count
reaches zero.
</member>
<member name="M:Poco.RefCountedObject.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\refcountedobject.h" line="51">
Returns the reference count.
</member>
<member name="M:Poco.RefCountedObject.#ctor(Poco.RefCountedObject!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\refcountedobject.h" line="55">
Destroys the RefCountedObject.
</member>
<member name="T:Poco.Timestamp" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="34">
A Timestamp stores a monotonic* time value
with (theoretical) microseconds resolution.
Timestamps can be compared with each other
and simple arithmetic is supported.

[*] Note that Timestamp values are only monotonic as
long as the systems's clock is monotonic as well
(and not, e.g. set back due to time synchronization
or other reasons).

Timestamps are UTC (Coordinated Universal Time)
based and thus independent of the timezone
in effect on the system.

The internal reference time is the Unix epoch, 
midnight, January 1, 1970.
</member>
<member name="D:Poco.Timestamp.UtcTimeVal" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="53">
Monotonic UTC time value in microsecond resolution,
with base time midnight, January 1, 1970.
</member>
<member name="D:Poco.Timestamp.TimeDiff" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="57">
Monotonic UTC time value in 100 nanosecond resolution,
with base time midnight, October 15, 1582.
</member>
<member name="F:Poco.Timestamp.TIMEVAL_MIN" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="61">
Difference between two TimeVal values in microseconds.
</member>
<member name="M:Poco.Timestamp.#ctor(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="67">
Creates a timestamp with the current time.
</member>
<member name="M:Poco.Timestamp.#ctor(Poco.Timestamp!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="70">
Creates a timestamp from the given time value
(microseconds since midnight, January 1, 1970).
</member>
<member name="M:Poco.Timestamp.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="74">
Copy constructor.
</member>
<member name="M:Poco.Timestamp.op_Assign(Poco.Timestamp!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="77">
Destroys the timestamp
</member>
<member name="M:Poco.Timestamp.update" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="83">
Swaps the Timestamp with another one.
</member>
<member name="M:Poco.Timestamp.op_Equality(Poco.Timestamp!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="86">
Updates the Timestamp with the current time.
</member>
<member name="M:Poco.Timestamp.utcTime" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="106">
Returns the timestamp expressed in time_t.
time_t base time is midnight, January 1, 1970.
Resolution is one second.
</member>
<member name="M:Poco.Timestamp.epochMicroseconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="111">
Returns the timestamp expressed in UTC-based
time. UTC base time is midnight, October 15, 1582.
Resolution is 100 nanoseconds.
</member>
<member name="M:Poco.Timestamp.elapsed" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="116">
Returns the timestamp expressed in microseconds
since the Unix epoch, midnight, January 1, 1970.
</member>
<member name="M:Poco.Timestamp.isElapsed(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="120">
Returns the time elapsed since the time denoted by
the timestamp. Equivalent to Timestamp() - *this.
</member>
<member name="M:Poco.Timestamp.raw" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="124">
Returns true iff the given interval has passed
since the time denoted by the timestamp.
</member>
<member name="M:Poco.Timestamp.fromEpochTime(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="128">
Returns the raw time value.

Same as epochMicroseconds().
</member>
<member name="M:Poco.Timestamp.fromUtcTime(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="133">
Creates a timestamp from a std::time_t.
</member>
<member name="M:Poco.Timestamp.resolution" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="136">
Creates a timestamp from a UTC time value
(100 nanosecond intervals since midnight,
October 15, 1582).
</member>
<member name="M:Poco.Timestamp.fromFileTimeNP(System.UInt32,System.UInt32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timestamp.h" line="141">
Returns the resolution in units per second.
Since the timestamp has microsecond resolution,
the returned value is always 1000000.
</member>
<member name="T:Poco.Timespan" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="31">
A class that represents time spans up to microsecond resolution.
</member>
<member name="M:Poco.Timespan.#ctor(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="37">
Creates a zero Timespan.
</member>
<member name="M:Poco.Timespan.#ctor(System.Int32!System.Runtime.CompilerServices.IsLong,System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="40">
Creates a Timespan.
</member>
<member name="M:Poco.Timespan.#ctor(System.Int32,System.Int32,System.Int32,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="43">
Creates a Timespan. Useful for creating
a Timespan from a struct timeval.
</member>
<member name="M:Poco.Timespan.#ctor(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="47">
Creates a Timespan.
</member>
<member name="M:Poco.Timespan.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="50">
Creates a Timespan from another one.
</member>
<member name="M:Poco.Timespan.op_Assign(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="53">
Destroys the Timespan.
</member>
<member name="M:Poco.Timespan.op_Assign(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="56">
Assignment operator.
</member>
<member name="M:Poco.Timespan.assign(System.Int32,System.Int32,System.Int32,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="59">
Assignment operator.
</member>
<member name="M:Poco.Timespan.assign(System.Int32!System.Runtime.CompilerServices.IsLong,System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="62">
Assigns a new span.
</member>
<member name="M:Poco.Timespan.swap(Poco.Timespan*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="65">
Assigns a new span. Useful for assigning
from a struct timeval.
</member>
<member name="M:Poco.Timespan.op_Equality(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="69">
Swaps the Timespan with another one.
</member>
<member name="M:Poco.Timespan.hours" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="96">
Returns the number of days.
</member>
<member name="M:Poco.Timespan.totalHours" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="99">
Returns the number of hours (0 to 23).
</member>
<member name="M:Poco.Timespan.minutes" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="102">
Returns the total number of hours.
</member>
<member name="M:Poco.Timespan.totalMinutes" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="105">
Returns the number of minutes (0 to 59).
</member>
<member name="M:Poco.Timespan.seconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="108">
Returns the total number of minutes.
</member>
<member name="M:Poco.Timespan.totalSeconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="111">
Returns the number of seconds (0 to 59).
</member>
<member name="M:Poco.Timespan.milliseconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="114">
Returns the total number of seconds.
</member>
<member name="M:Poco.Timespan.totalMilliseconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="117">
Returns the number of milliseconds (0 to 999).
</member>
<member name="M:Poco.Timespan.microseconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="120">
Returns the total number of milliseconds.
</member>
<member name="M:Poco.Timespan.useconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="123">
Returns the fractions of a millisecond
in microseconds (0 to 999).
</member>
<member name="M:Poco.Timespan.totalMicroseconds" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="127">
Returns the fractions of a second
in microseconds (0 to 999999).
</member>
<member name="F:Poco.Timespan.MILLISECONDS" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\timespan.h" line="131">
Returns the total number of microseconds.
</member>
<member name="T:Poco.Net.SocketImpl.SelectMode" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="35">
This class encapsulates the Berkeley sockets API.

Subclasses implement specific socket types like
stream or datagram sockets.

You should not create any instances of this class.
</member>
<member name="M:Poco.Net.SocketImpl.connect(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="51">
Get the next completed connection from the
socket's completed connection queue.

If the queue is empty, waits until a connection
request completes.

Returns a new TCP socket for the connection
with the client.

The client socket's address is returned in clientAddr.
</member>
<member name="M:Poco.Net.SocketImpl.connect(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="63">
Initializes the socket and establishes a connection to 
the TCP server at the given address.

Can also be used for UDP sockets. In this case, no
connection is established. Instead, incoming and outgoing
packets are restricted to the specified address.
</member>
<member name="M:Poco.Net.SocketImpl.connectNB(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="71">
Initializes the socket, sets the socket timeout and 
establishes a connection to the TCP server at the given address.
</member>
<member name="M:Poco.Net.SocketImpl.bind(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="75">
Initializes the socket and establishes a connection to 
the TCP server at the given address. Prior to opening the
connection the socket is set to nonblocking mode.
</member>
<member name="M:Poco.Net.SocketImpl.bind(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="80">
Bind a local address to the socket.

This is usually only done when establishing a server
socket. TCP clients should not bind a socket to a
specific address.

If reuseAddress is true, sets the SO_REUSEADDR
socket option.
</member>
<member name="M:Poco.Net.SocketImpl.bind6(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="90">
Bind a local address to the socket.

This is usually only done when establishing a server
socket. TCP clients should not bind a socket to a
specific address.

If reuseAddress is true, sets the SO_REUSEADDR
socket option.

If reusePort is true, sets the SO_REUSEPORT
socket option.
</member>
<member name="M:Poco.Net.SocketImpl.bind6(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean,System.Boolean,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="103">
Bind a local IPv6 address to the socket.

This is usually only done when establishing a server
socket. TCP clients should not bind a socket to a
specific address.

If reuseAddress is true, sets the SO_REUSEADDR
socket option.

The given address must be an IPv6 address. The
IPPROTO_IPV6/IPV6_V6ONLY option is set on the socket
according to the ipV6Only parameter.

If the library has not been built with IPv6 support,
a Poco::NotImplementedException will be thrown.
</member>
<member name="M:Poco.Net.SocketImpl.listen(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="120">
Bind a local IPv6 address to the socket.

This is usually only done when establishing a server
socket. TCP clients should not bind a socket to a
specific address.

If reuseAddress is true, sets the SO_REUSEADDR
socket option.

If reusePort is true, sets the SO_REUSEPORT
socket option.

The given address must be an IPv6 address. The
IPPROTO_IPV6/IPV6_V6ONLY option is set on the socket
according to the ipV6Only parameter.

If the library has not been built with IPv6 support,
a Poco::NotImplementedException will be thrown.
</member>
<member name="M:Poco.Net.SocketImpl.close" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="140">
Puts the socket into listening state.

The socket becomes a passive socket that
can accept incoming connection requests.

The backlog argument specifies the maximum
number of connections that can be queued
for this socket.
</member>
<member name="M:Poco.Net.SocketImpl.shutdownReceive" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="150">
Close the socket.
</member>
<member name="M:Poco.Net.SocketImpl.shutdownSend" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="153">
Shuts down the receiving part of the socket connection.
</member>
<member name="M:Poco.Net.SocketImpl.shutdown" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="156">
Shuts down the sending part of the socket connection.
</member>
<member name="M:Poco.Net.SocketImpl.sendBytes(System.Void!System.Runtime.CompilerServices.IsConst*,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="159">
Shuts down both the receiving and the sending part
of the socket connection.
</member>
<member name="M:Poco.Net.SocketImpl.receiveBytes(System.Void*,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="163">
Sends the contents of the given buffer through
the socket.

Returns the number of bytes sent, which may be
less than the number of bytes specified.

Certain socket implementations may also return a negative
value denoting a certain condition.
</member>
<member name="M:Poco.Net.SocketImpl.sendTo(System.Void!System.Runtime.CompilerServices.IsConst*,System.Int32,Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="173">
Receives data from the socket and stores it
in buffer. Up to length bytes are received.

Returns the number of bytes received.

Certain socket implementations may also return a negative
value denoting a certain condition.
</member>
<member name="M:Poco.Net.SocketImpl.receiveFrom(System.Void*,System.Int32,Poco.Net.SocketAddress*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="182">
Sends the contents of the given buffer through
the socket to the given address.

Returns the number of bytes sent, which may be
less than the number of bytes specified.
</member>
<member name="M:Poco.Net.SocketImpl.sendUrgent(System.Byte)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="189">
Receives data from the socket and stores it
in buffer. Up to length bytes are received.
Stores the address of the sender in address.

Returns the number of bytes received.
</member>
<member name="M:Poco.Net.SocketImpl.available" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="196">
Sends one byte of urgent data through
the socket.

The data is sent with the MSG_OOB flag.

The preferred way for a socket to receive urgent data
is by enabling the SO_OOBINLINE option.
</member>
<member name="M:Poco.Net.SocketImpl.poll(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="205">
Returns the number of bytes available that can be read
without causing the socket to block.
</member>
<member name="M:Poco.Net.SocketImpl.setSendBufferSize(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="209">
Determines the status of the socket, using a 
call to select().

The mode argument is constructed by combining the values
of the SelectMode enumeration.

Returns true if the next operation corresponding to
mode will not block, false otherwise.
</member>
<member name="M:Poco.Net.SocketImpl.getSendBufferSize" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="219">
Sets the size of the send buffer.
</member>
<member name="M:Poco.Net.SocketImpl.setReceiveBufferSize(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="222">
Returns the size of the send buffer.

The returned value may be different than the
value previously set with setSendBufferSize(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.SocketImpl.getReceiveBufferSize" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="229">
Sets the size of the receive buffer.
</member>
<member name="M:Poco.Net.SocketImpl.setSendTimeout(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="232">
Returns the size of the receive buffer.

The returned value may be different than the
value previously set with setReceiveBufferSize(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.SocketImpl.getSendTimeout" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="239">
Sets the send timeout for the socket.
</member>
<member name="M:Poco.Net.SocketImpl.setReceiveTimeout(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="242">
Returns the send timeout for the socket.

The returned timeout may be different than the
timeout previously set with setSendTimeout(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.SocketImpl.getReceiveTimeout" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="249">
Sets the send timeout for the socket.

On systems that do not support SO_RCVTIMEO, a
workaround using poll() is provided.
</member>
<member name="M:Poco.Net.SocketImpl.address" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="255">
Returns the receive timeout for the socket.

The returned timeout may be different than the
timeout previously set with setReceiveTimeout(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.SocketImpl.peerAddress" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="262">
Returns the IP address and port number of the socket.
</member>
<member name="M:Poco.Net.SocketImpl.setOption(System.Int32,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="265">
Returns the IP address and port number of the peer socket.
</member>
<member name="M:Poco.Net.SocketImpl.setOption(System.Int32,System.Int32,System.UInt32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="268">
Sets the socket option specified by level and option
to the given integer value.
</member>
<member name="M:Poco.Net.SocketImpl.setOption(System.Int32,System.Int32,System.Byte)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="272">
Sets the socket option specified by level and option
to the given integer value.
</member>
<member name="M:Poco.Net.SocketImpl.setOption(System.Int32,System.Int32,Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="276">
Sets the socket option specified by level and option
to the given integer value.
</member>
<member name="M:Poco.Net.SocketImpl.setOption(System.Int32,System.Int32,Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="280">
Sets the socket option specified by level and option
to the given time value.
</member>
<member name="M:Poco.Net.SocketImpl.setRawOption(System.Int32,System.Int32,System.Void!System.Runtime.CompilerServices.IsConst*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="284">
Sets the socket option specified by level and option
to the given time value.
</member>
<member name="M:Poco.Net.SocketImpl.getOption(System.Int32,System.Int32,System.Int32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="288">
Sets the socket option specified by level and option
to the given time value.
</member>
<member name="M:Poco.Net.SocketImpl.getOption(System.Int32,System.Int32,System.UInt32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="292">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.SocketImpl.getOption(System.Int32,System.Int32,System.Byte*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="296">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.SocketImpl.getOption(System.Int32,System.Int32,Poco.Timespan*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="300">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.SocketImpl.getOption(System.Int32,System.Int32,Poco.Net.IPAddress*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="304">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.SocketImpl.getRawOption(System.Int32,System.Int32,System.Void*,System.Int32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="308">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.SocketImpl.setLinger(System.Boolean,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="312">
Returns the value of the socket option 
specified by level and option.	
</member>
<member name="M:Poco.Net.SocketImpl.getLinger(System.Boolean*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="316">
Sets the value of the SO_LINGER socket option.
</member>
<member name="M:Poco.Net.SocketImpl.setNoDelay(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="319">
Returns the value of the SO_LINGER socket option.
</member>
<member name="M:Poco.Net.SocketImpl.getNoDelay" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="322">
Sets the value of the TCP_NODELAY socket option.
</member>
<member name="M:Poco.Net.SocketImpl.setKeepAlive(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="325">
Returns the value of the TCP_NODELAY socket option.
</member>
<member name="M:Poco.Net.SocketImpl.getKeepAlive" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="328">
Sets the value of the SO_KEEPALIVE socket option.
</member>
<member name="M:Poco.Net.SocketImpl.setReuseAddress(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="331">
Returns the value of the SO_KEEPALIVE socket option.
</member>
<member name="M:Poco.Net.SocketImpl.getReuseAddress" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="334">
Sets the value of the SO_REUSEADDR socket option.
</member>
<member name="M:Poco.Net.SocketImpl.setReusePort(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="337">
Returns the value of the SO_REUSEADDR socket option.
</member>
<member name="M:Poco.Net.SocketImpl.getReusePort" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="340">
Sets the value of the SO_REUSEPORT socket option.
Does nothing if the socket implementation does not
support SO_REUSEPORT.
</member>
<member name="M:Poco.Net.SocketImpl.setOOBInline(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="345">
Returns the value of the SO_REUSEPORT socket option.

Returns false if the socket implementation does not
support SO_REUSEPORT.
</member>
<member name="M:Poco.Net.SocketImpl.getOOBInline" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="351">
Sets the value of the SO_OOBINLINE socket option.
</member>
<member name="M:Poco.Net.SocketImpl.setBroadcast(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="354">
Returns the value of the SO_OOBINLINE socket option.
</member>
<member name="M:Poco.Net.SocketImpl.getBroadcast" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="357">
Sets the value of the SO_BROADCAST socket option.
</member>
<member name="M:Poco.Net.SocketImpl.setBlocking(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="360">
Returns the value of the SO_BROADCAST socket option.
</member>
<member name="M:Poco.Net.SocketImpl.getBlocking" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="363">
Sets the socket in blocking mode if flag is true,
disables blocking mode if flag is false.
</member>
<member name="M:Poco.Net.SocketImpl.secure" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="367">
Returns the blocking mode of the socket.
This method will only work if the blocking modes of
the socket are changed via the setBlocking method!
</member>
<member name="M:Poco.Net.SocketImpl.socketError" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="372">
Returns true iff the socket's connection is secure
(using SSL or TLS).
</member>
<member name="M:Poco.Net.SocketImpl.sockfd" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="376">
Returns the value of the SO_ERROR socket option.
</member>
<member name="M:Poco.Net.SocketImpl.ioctl(System.Int32,System.Int32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="379">
Returns the socket descriptor for the
underlying native socket.
</member>
<member name="M:Poco.Net.SocketImpl.ioctl(System.Int32,System.Void*)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="383">
A wrapper for the ioctl system call.
</member>
<member name="M:Poco.Net.SocketImpl.initialized" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="386">
A wrapper for the ioctl system call.
</member>
<member name="M:Poco.Net.SocketImpl.#ctor" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="397">
Returns true iff the underlying socket is initialized.
</member>
<member name="M:Poco.Net.SocketImpl.#ctor(System.UInt64)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="401">
Creates a SocketImpl.
</member>
<member name="M:Poco.Net.SocketImpl.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="404">
Creates a SocketImpl using the given native socket.
</member>
<member name="M:Poco.Net.SocketImpl.init(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="407">
Destroys the SocketImpl.
Closes the socket if it is still open.
</member>
<member name="M:Poco.Net.SocketImpl.initSocket(System.Int32,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="411">
Creates the underlying native socket.

Subclasses must implement this method so
that it calls initSocket() with the
appropriate arguments.

The default implementation creates a
stream socket.
</member>
<member name="M:Poco.Net.SocketImpl.reset(System.UInt64)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="421">
Creates the underlying native socket.

The first argument, af, specifies the address family
used by the socket, which should be either AF_INET or
AF_INET6.

The second argument, type, specifies the type of the
socket, which can be one of SOCK_STREAM, SOCK_DGRAM
or SOCK_RAW.

The third argument, proto, is normally set to 0,
except for raw sockets.
</member>
<member name="M:Poco.Net.SocketImpl.lastError" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="435">
Allows subclasses to set the socket manually, iff no valid socket is set yet.
</member>
<member name="M:Poco.Net.SocketImpl.error" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="438">
Returns the last error code.
</member>
<member name="M:Poco.Net.SocketImpl.error(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="441">
Throws an appropriate exception for the last error.
</member>
<member name="M:Poco.Net.SocketImpl.error(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="444">
Throws an appropriate exception for the last error.
</member>
<member name="M:Poco.Net.SocketImpl.error(System.Int32,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="447">
Throws an appropriate exception for the given error code.
</member>
<member name="M:Poco.Net.SocketImpl.#ctor(Poco.Net.SocketImpl!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socketimpl.h" line="450">
Throws an appropriate exception for the given error code.
</member>
<member name="T:Poco.Net.Socket" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="33">
Socket is the common base class for
StreamSocket, ServerSocket, DatagramSocket and other
socket classes.

It provides operations common to all socket types.
</member>
<member name="T:Poco.Net.Socket.SelectMode" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="41">
The mode argument to poll() and select().
</member>
<member name="M:Poco.Net.Socket.#ctor(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="51">
Creates an uninitialized socket.
</member>
<member name="M:Poco.Net.Socket.op_Assign(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="54">
Copy constructor.

Attaches the SocketImpl from the other socket and
increments the reference count of the SocketImpl.
</member>
<member name="M:Poco.Net.Socket.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="60">
Assignment operator.

Releases the socket's SocketImpl and
attaches the SocketImpl from the other socket and
increments the reference count of the SocketImpl.
</member>
<member name="M:Poco.Net.Socket.op_Equality(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="67">
Destroys the Socket and releases the
SocketImpl.
</member>
<member name="M:Poco.Net.Socket.op_Inequality(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="71">
Returns true if both sockets share the same
SocketImpl, false otherwise.
</member>
<member name="M:Poco.Net.Socket.op_LessThan(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="75">
Returns false if both sockets share the same
SocketImpl, true otherwise.
</member>
<member name="M:Poco.Net.Socket.op_LessThanOrEqual(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="79">
Compares the SocketImpl pointers.
</member>
<member name="M:Poco.Net.Socket.op_GreaterThan(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="82">
Compares the SocketImpl pointers.
</member>
<member name="M:Poco.Net.Socket.op_GreaterThanOrEqual(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="85">
Compares the SocketImpl pointers.
</member>
<member name="M:Poco.Net.Socket.close" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="88">
Compares the SocketImpl pointers.
</member>
<member name="M:Poco.Net.Socket.select(std.vector&lt;Poco.Net.Socket,std.allocator&lt;Poco.Net.Socket&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.vector&lt;Poco.Net.Socket,std.allocator&lt;Poco.Net.Socket&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.vector&lt;Poco.Net.Socket,std.allocator&lt;Poco.Net.Socket&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="91">
Closes the socket.
</member>
<member name="M:Poco.Net.Socket.poll(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="94">
Determines the status of one or more sockets, 
using a call to select().

ReadList contains the list of sockets which should be
checked for readability.

WriteList contains the list of sockets which should be
checked for writeability.

ExceptList contains a list of sockets which should be
checked for a pending error.

Returns the number of sockets ready.

After return, 
  * readList contains those sockets ready for reading,
  * writeList contains those sockets ready for writing,
  * exceptList contains those sockets with a pending error.

If the total number of sockets passed in readList, writeList and
exceptList is zero, select() will return immediately and the
return value will be 0.

If one of the sockets passed to select() is closed while
select() runs, select will return immediately. However,
the closed socket will not be included in any list.
In this case, the return value may be greater than the sum
of all sockets in all list.
</member>
<member name="M:Poco.Net.Socket.available" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="124">
Determines the status of the socket, using a 
call to poll() or select().

The mode argument is constructed by combining the values
of the SelectMode enumeration.

Returns true if the next operation corresponding to
mode will not block, false otherwise.
</member>
<member name="M:Poco.Net.Socket.setSendBufferSize(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="134">
Returns the number of bytes available that can be read
without causing the socket to block.
</member>
<member name="M:Poco.Net.Socket.getSendBufferSize" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="138">
Sets the size of the send buffer.
</member>
<member name="M:Poco.Net.Socket.setReceiveBufferSize(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="141">
Returns the size of the send buffer.

The returned value may be different than the
value previously set with setSendBufferSize(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.Socket.getReceiveBufferSize" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="148">
Sets the size of the receive buffer.
</member>
<member name="M:Poco.Net.Socket.setSendTimeout(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="151">
Returns the size of the receive buffer.

The returned value may be different than the
value previously set with setReceiveBufferSize(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.Socket.getSendTimeout" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="158">
Sets the send timeout for the socket.
</member>
<member name="M:Poco.Net.Socket.setReceiveTimeout(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="161">
Returns the send timeout for the socket.

The returned timeout may be different than the
timeout previously set with setSendTimeout(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.Socket.getReceiveTimeout" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="168">
Sets the send timeout for the socket.

On systems that do not support SO_RCVTIMEO, a
workaround using poll() is provided.
</member>
<member name="M:Poco.Net.Socket.setOption(System.Int32,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="174">
Returns the receive timeout for the socket.

The returned timeout may be different than the
timeout previously set with getReceiveTimeout(),
as the system is free to adjust the value.
</member>
<member name="M:Poco.Net.Socket.setOption(System.Int32,System.Int32,System.UInt32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="181">
Sets the socket option specified by level and option
to the given integer value.
</member>
<member name="M:Poco.Net.Socket.setOption(System.Int32,System.Int32,System.Byte)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="185">
Sets the socket option specified by level and option
to the given integer value.
</member>
<member name="M:Poco.Net.Socket.setOption(System.Int32,System.Int32,Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="189">
Sets the socket option specified by level and option
to the given integer value.
</member>
<member name="M:Poco.Net.Socket.setOption(System.Int32,System.Int32,Poco.Net.IPAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="193">
Sets the socket option specified by level and option
to the given time value.
</member>
<member name="M:Poco.Net.Socket.getOption(System.Int32,System.Int32,System.Int32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="197">
Sets the socket option specified by level and option
to the given time value.
</member>
<member name="M:Poco.Net.Socket.getOption(System.Int32,System.Int32,System.UInt32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="201">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.Socket.getOption(System.Int32,System.Int32,System.Byte*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="205">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.Socket.getOption(System.Int32,System.Int32,Poco.Timespan*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="209">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.Socket.getOption(System.Int32,System.Int32,Poco.Net.IPAddress*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="213">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.Socket.setLinger(System.Boolean,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="217">
Returns the value of the socket option 
specified by level and option.
</member>
<member name="M:Poco.Net.Socket.getLinger(System.Boolean*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="221">
Sets the value of the SO_LINGER socket option.
</member>
<member name="M:Poco.Net.Socket.setNoDelay(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="224">
Returns the value of the SO_LINGER socket option.
</member>
<member name="M:Poco.Net.Socket.getNoDelay" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="227">
Sets the value of the TCP_NODELAY socket option.
</member>
<member name="M:Poco.Net.Socket.setKeepAlive(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="230">
Returns the value of the TCP_NODELAY socket option.
</member>
<member name="M:Poco.Net.Socket.getKeepAlive" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="233">
Sets the value of the SO_KEEPALIVE socket option.
</member>
<member name="M:Poco.Net.Socket.setReuseAddress(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="236">
Returns the value of the SO_KEEPALIVE socket option.
</member>
<member name="M:Poco.Net.Socket.getReuseAddress" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="239">
Sets the value of the SO_REUSEADDR socket option.
</member>
<member name="M:Poco.Net.Socket.setReusePort(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="242">
Returns the value of the SO_REUSEADDR socket option.
</member>
<member name="M:Poco.Net.Socket.getReusePort" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="245">
Sets the value of the SO_REUSEPORT socket option.
Does nothing if the socket implementation does not
support SO_REUSEPORT.
</member>
<member name="M:Poco.Net.Socket.setOOBInline(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="250">
Returns the value of the SO_REUSEPORT socket option.

Returns false if the socket implementation does not
support SO_REUSEPORT.
</member>
<member name="M:Poco.Net.Socket.getOOBInline" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="256">
Sets the value of the SO_OOBINLINE socket option.
</member>
<member name="M:Poco.Net.Socket.setBlocking(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="259">
Returns the value of the SO_OOBINLINE socket option.
</member>
<member name="M:Poco.Net.Socket.getBlocking" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="262">
Sets the socket in blocking mode if flag is true,
disables blocking mode if flag is false.
</member>
<member name="M:Poco.Net.Socket.address" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="266">
Returns the blocking mode of the socket.
This method will only work if the blocking modes of 
the socket are changed via the setBlocking method!
</member>
<member name="M:Poco.Net.Socket.peerAddress" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="271">
Returns the IP address and port number of the socket.
</member>
<member name="M:Poco.Net.Socket.impl" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="274">
Returns the IP address and port number of the peer socket.
</member>
<member name="M:Poco.Net.Socket.secure" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="277">
Returns the SocketImpl for this socket.
</member>
<member name="M:Poco.Net.Socket.supportsIPv4" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="280">
Returns true iff the socket's connection is secure
(using SSL or TLS).
</member>
<member name="M:Poco.Net.Socket.supportsIPv6" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="284">
Returns true if the system supports IPv4.
</member>
<member name="M:Poco.Net.Socket.init(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="287">
Returns true if the system supports IPv6.
</member>
<member name="M:Poco.Net.Socket.#ctor(Poco.Net.SocketImpl*)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="290">
Creates the underlying system socket for the given
address family.

Normally, this method should not be called directly, as
socket creation will be handled automatically. There are
a few situations where calling this method after creation
of the Socket object makes sense. One example is setting
a socket option before calling bind() on a ServerSocket.
</member>
<member name="M:Poco.Net.Socket.sockfd" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="301">
Creates the Socket and attaches the given SocketImpl.
The socket takes ownership of the SocketImpl.
</member>
<member name="F:Poco.Net.Socket._pImpl" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\socket.h" line="305">
Returns the socket descriptor for this socket.
</member>
<member name="T:Poco.ReferenceCounter" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\sharedptr.h" line="33">
Simple ReferenceCounter object, does not delete itself when count reaches 0.
</member>
<member name="T:Poco.Event.EventType" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="40">
An Event is a synchronization object that
allows one thread to signal one or more
other threads that a certain event
has happened.
Usually, one thread signals an event,
while one or more other threads wait
for an event to become signalled.
</member>
<member name="M:Poco.Event.#ctor(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="56">
Creates the event. If type is EVENT_AUTORESET,
the event is automatically reset after
a wait() successfully returns.
</member>
<member name="M:Poco.Event.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="62">
Please use Event::Event(EventType) instead.
</member>
<member name="M:Poco.Event.set" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="65">
Destroys the event.
</member>
<member name="M:Poco.Event.wait" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="68">
Signals the event. If autoReset is true,
only one thread waiting for the event 
can resume execution.
If autoReset is false, all waiting threads
can resume execution.
</member>
<member name="M:Poco.Event.wait(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="75">
Waits for the event to become signalled.
</member>
<member name="M:Poco.Event.tryWait(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="78">
Waits for the event to become signalled.
Throws a TimeoutException if the event
does not become signalled within the specified
time interval.
</member>
<member name="M:Poco.Event.reset" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="84">
Waits for the event to become signalled.
Returns true if the event
became signalled within the specified
time interval, false otherwise.
</member>
<member name="M:Poco.Event.#ctor(Poco.Event!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\event.h" line="90">
Resets the event to unsignalled state.
</member>
<member name="T:Poco.Runnable" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\runnable.h" line="30">
The Runnable interface with the run() method
must be implemented by classes that provide
an entry point for a thread.
</member>
<member name="D:Poco.ActiveRunnableBase.Ptr" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\activerunnable.h" line="35">
The base class for all ActiveRunnable instantiations.
</member>
<member name="T:Poco.Environment" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="30">
This class provides access to environment variables
and some general system information.
</member>
<member name="M:Poco.Environment.get(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="37">
Returns the value of the environment variable
with the given name. Throws a NotFoundException
if the variable does not exist.
</member>
<member name="M:Poco.Environment.has(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="42">
Returns the value of the environment variable
with the given name. If the environment variable
is undefined, returns defaultValue instead.
</member>
<member name="M:Poco.Environment.set(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="47">
Returns true iff an environment variable
with the given name is defined.
</member>
<member name="M:Poco.Environment.osName" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="51">
Sets the environment variable with the given name
to the given value.
</member>
<member name="M:Poco.Environment.osDisplayName" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="55">
Returns the operating system name.
</member>
<member name="M:Poco.Environment.osVersion" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="58">
Returns the operating system name in a
"user-friendly" way.

Currently this is only implemented for
Windows. There it will return names like
"Windows XP" or "Windows 7/Server 2008 SP2".
On other platforms, returns the same as
osName().
</member>
<member name="M:Poco.Environment.osArchitecture" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="68">
Returns the operating system version.
</member>
<member name="M:Poco.Environment.nodeName" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="71">
Returns the operating system architecture.
</member>
<member name="M:Poco.Environment.nodeId(System.Byte(*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)[N6])" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="74">
Returns the node (or host) name.
</member>
<member name="M:Poco.Environment.nodeId" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="77">
Returns the Ethernet address of the first Ethernet
adapter found on the system.

Throws a SystemException if no Ethernet adapter is available.
</member>
<member name="M:Poco.Environment.processorCount" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="83">
Returns the Ethernet address (format "xx:xx:xx:xx:xx:xx")
of the first Ethernet adapter found on the system.

Throws a SystemException if no Ethernet adapter is available.
</member>
<member name="M:Poco.Environment.libraryVersion" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\environment.h" line="89">
Returns the number of processors installed in the system.

If the number of processors cannot be determined, returns 1.
</member>
<member name="D:Poco.Thread.TID" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="50">
This class implements a platform-independent
wrapper to an operating system thread.

Every Thread object gets a unique (within
its process) numeric thread ID.
Furthermore, a thread can be assigned a name.
The name of a thread can be changed at any time.
</member>
<member name="T:Poco.Thread.Priority" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="64">
Thread priorities.
</member>
<member name="M:Poco.Thread.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="79">
Creates a thread. Call start() to start it.
</member>
<member name="M:Poco.Thread.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="82">
Creates a named thread. Call start() to start it.
</member>
<member name="M:Poco.Thread.id" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="85">
Destroys the thread.
</member>
<member name="M:Poco.Thread.tid" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="88">
Returns the unique thread ID of the thread.
</member>
<member name="M:Poco.Thread.name" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="91">
Returns the native thread ID of the thread.
</member>
<member name="M:Poco.Thread.getName" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="94">
Returns the name of the thread.
</member>
<member name="M:Poco.Thread.setName(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="97">
Returns the name of the thread.
</member>
<member name="M:Poco.Thread.setPriority(Poco.Thread.Priority)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="100">
Sets the name of the thread.
</member>
<member name="M:Poco.Thread.getPriority" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="103">
Sets the thread's priority.

Some platform only allow changing a thread's priority
if the process has certain privileges.
</member>
<member name="M:Poco.Thread.setOSPriority(System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="109">
Returns the thread's priority.
</member>
<member name="M:Poco.Thread.getOSPriority" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="112">
Sets the thread's priority, using an operating system specific
priority value. Use getMinOSPriority() and getMaxOSPriority() to
obtain minimum and maximum priority values. Additionally,
a scheduling policy can be specified. The policy is currently
only used on POSIX platforms where the values SCHED_OTHER (default),
SCHED_FIFO and SCHED_RR are supported.
</member>
<member name="M:Poco.Thread.getMinOSPriority(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="120">
Returns the thread's priority, expressed as an operating system
specific priority value.

May return 0 if the priority has not been explicitly set.
</member>
<member name="M:Poco.Thread.getMaxOSPriority(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="126">
Returns the minimum operating system-specific priority value,
which can be passed to setOSPriority() for the given policy.
</member>
<member name="M:Poco.Thread.setStackSize(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="130">
Returns the maximum operating system-specific priority value,
which can be passed to setOSPriority() for the given policy.
</member>
<member name="M:Poco.Thread.setAffinity(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="134">
Sets the thread's stack size in bytes.
Setting the stack size to 0 will use the default stack size.
Typically, the real stack size is rounded up to the nearest
page size multiple.
</member>
<member name="M:Poco.Thread.getAffinity" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="140">
Binds the thread to run only on the CPU core with the 
given index.

Does nothing if the system does not support CPU affinity for
threads.
</member>
<member name="M:Poco.Thread.getStackSize" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="147">
Returns the index of the CPU core this thread has been bound to,
or -1 if the thread has not been bound to a CPU.
</member>
<member name="M:Poco.Thread.start(Poco.Runnable*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="151">
Returns the thread's stack size in bytes.
If the default stack size is used, 0 is returned.
</member>
<member name="M:Poco.Thread.start(=FUNC:System.Void(System.Void*),System.Void*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="155">
Starts the thread with the given target.

Note that the given Runnable object must remain
valid during the entire lifetime of the thread, as
only a reference to it is stored internally.
</member>
<member name="M:Poco.Thread.join(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="172">
Waits until the thread completes execution.
If multiple threads try to join the same
thread, the result is undefined.
</member>
<member name="M:Poco.Thread.tryJoin(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="177">
Waits for at most the given interval for the thread
to complete. Throws a TimeoutException if the thread
does not complete within the specified time interval.
</member>
<member name="M:Poco.Thread.isRunning" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="182">
Waits for at most the given interval for the thread
to complete. Returns true if the thread has finished,
false otherwise.
</member>
<member name="M:Poco.Thread.trySleep(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="187">
Returns true if the thread is running.
</member>
<member name="M:Poco.Thread.wakeUp" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="190">
Starts an interruptible sleep. When trySleep() is called,
the thread will remain suspended until:
  - the timeout expires or
  - wakeUp() is called

Function returns true if sleep attempt was completed, false
if sleep was interrupted by a wakeUp() call.
A frequent scenario where trySleep()/wakeUp() pair of functions
is useful is with threads spending most of the time idle,
with periodic activity between the idle times; trying to sleep
(as opposed to sleeping) allows immediate ending of idle thread
from the outside.

The trySleep() and wakeUp() calls should be used with
understanding that the suspended state is not a true sleep,
but rather a state of waiting for an event, with timeout
expiration. This makes order of calls significant; calling
wakeUp() before calling trySleep() will prevent the next
trySleep() call to actually suspend the thread (which, in
some scenarios, may be desirable behavior).
</member>
<member name="M:Poco.Thread.sleep(System.Int32!System.Runtime.CompilerServices.IsLong)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="212">
Wakes up the thread which is in the state of interruptible
sleep. For threads that are not suspended, calling this
function has the effect of preventing the subsequent
trySleep() call to put thread in a suspended state.
</member>
<member name="M:Poco.Thread.yield" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="218">
Suspends the current thread for the specified
amount of time.
</member>
<member name="M:Poco.Thread.current" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="222">
Yields cpu to other threads.
</member>
<member name="M:Poco.Thread.currentTid" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="225">
Returns the Thread object for the currently active thread.
If the current thread is the main thread, 0 is returned.
</member>
<member name="M:Poco.Thread.tls" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="229">
Returns the native thread ID for the current thread.
</member>
<member name="M:Poco.Thread.clearTLS" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="233">
Returns a reference to the thread's local storage.
</member>
<member name="M:Poco.Thread.makeName" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="236">
Clears the thread's local storage.
</member>
<member name="M:Poco.Thread.uniqueId" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\thread.h" line="239">
Creates a unique name for a thread.
</member>
<member name="T:Poco.ThreadPool" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="36">
A thread pool always keeps a number of threads running, ready
to accept work.
Creating and starting a threads can impose a significant runtime
overhead to an application. A thread pool helps to improve
the performance of an application by reducing the number
of threads that have to be created (and destroyed again).
Threads in a thread pool are re-used once they become
available again.
The thread pool always keeps a minimum number of threads
running. If the demand for threads increases, additional
threads are created. Once the demand for threads sinks
again, no-longer used threads are stopped and removed
from the pool.
</member>
<member name="M:Poco.ThreadPool.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32,System.Int32,System.Int32,System.Int32,Poco.ThreadPool.ThreadAffinityPolicy)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="63">
Creates a thread pool with minCapacity threads.
If required, up to maxCapacity threads are created
a NoThreadAvailableException exception is thrown.
If a thread is running idle for more than idleTime seconds,
and more than minCapacity threads are running, the thread
is killed. Threads are created with given stack size.
Threads are created with given affinity policy.
</member>
<member name="M:Poco.ThreadPool.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="77">
Creates a thread pool with the given name and minCapacity threads.
If required, up to maxCapacity threads are created
a NoThreadAvailableException exception is thrown.
If a thread is running idle for more than idleTime seconds,
and more than minCapacity threads are running, the thread
is killed. Threads are created with given stack size.
Threads are created with given affinity policy.
</member>
<member name="M:Poco.ThreadPool.addCapacity(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="86">
Currently running threads will remain active
until they complete. 
</member>
<member name="M:Poco.ThreadPool.capacity" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="90">
Increases (or decreases, if n is negative)
the maximum number of threads.
</member>
<member name="M:Poco.ThreadPool.setStackSize(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="94">
Returns the maximum capacity of threads.
</member>
<member name="M:Poco.ThreadPool.getStackSize" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="97">
Sets the stack size for threads.
New stack size applies only for newly created threads.
</member>
<member name="M:Poco.ThreadPool.setAffinityPolicy(Poco.ThreadPool.ThreadAffinityPolicy)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="101">
Returns the stack size used to create new threads.
</member>
<member name="M:Poco.ThreadPool.getAffinityPolicy" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="104">
Sets the thread affinity policy for newly created threads.
</member>
<member name="M:Poco.ThreadPool.used" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="107">
Returns the thread affinity policy used to create new threads.
</member>
<member name="M:Poco.ThreadPool.allocated" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="110">
Returns the number of currently used threads.
</member>
<member name="M:Poco.ThreadPool.available" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="113">
Returns the number of currently allocated threads.
</member>
<member name="M:Poco.ThreadPool.start(Poco.Runnable*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="116">
Returns the number available threads.
</member>
<member name="M:Poco.ThreadPool.start(Poco.Runnable*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="119">
Obtains a thread and starts the target on specified cpu.
Throws a NoThreadAvailableException if no more
threads are available.
</member>
<member name="M:Poco.ThreadPool.startWithPriority(Poco.Thread.Priority,Poco.Runnable*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="124">
Obtains a thread and starts the target on specified cpu.
Assigns the given name to the thread.
Throws a NoThreadAvailableException if no more
threads are available.
</member>
<member name="M:Poco.ThreadPool.startWithPriority(Poco.Thread.Priority,Poco.Runnable*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="130">
Obtains a thread, adjusts the thread's priority, and starts the target on specified cpu.
Throws a NoThreadAvailableException if no more
threads are available.
</member>
<member name="M:Poco.ThreadPool.stopAll" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="135">
Obtains a thread, adjusts the thread's priority, and starts the target on specified cpu.
Assigns the given name to the thread.
Throws a NoThreadAvailableException if no more
threads are available.
</member>
<member name="M:Poco.ThreadPool.joinAll" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="141">
Stops all running threads and waits for their completion.

Will also delete all thread objects.
If used, this method should be the last action before
the thread pool is deleted.

Note: If a thread fails to stop within 10 seconds 
(due to a programming error, for example), the
underlying thread object will not be deleted and
this method will return anyway. This allows for a
more or less graceful shutdown in case of a misbehaving
thread.
</member>
<member name="M:Poco.ThreadPool.collect" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="155">
Waits for all threads to complete.

Note that this will not actually join() the underlying
thread, but rather wait for the thread's runnables
to finish.
</member>
<member name="M:Poco.ThreadPool.name" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="162">
Stops and removes no longer used threads from the
thread pool. Can be called at various times in an
application's life time to help the thread pool
manage its threads. Calling this method is optional,
as the thread pool is also implicitly managed in
calls to start(), addCapacity() and joinAll().
</member>
<member name="M:Poco.ThreadPool.defaultPool(Poco.ThreadPool.ThreadAffinityPolicy)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="170">
Returns the name of the thread pool,
or an empty string if no name has been
specified in the constructor.
</member>
<member name="M:Poco.ThreadPool.getThread" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\threadpool.h" line="175">
Returns a reference to the default
thread pool.
</member>
<member name="T:Poco.Any" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\any.h" line="154">
An Any class represents a general type and is capable of storing any type, supporting type-safe extraction
of the internally stored data.

Code taken from the Boost 1.33.1 library. Original copyright by Kevlin Henney. Modified for Poco
by Applied Informatics.

Modified for small object optimization support (optionally supported through conditional compilation)
by Alex Fabijanic.
</member>
<member name="M:Poco.Any.swap(Poco.Any*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\any.h" line="388">
Swaps the content of the two Anys.
</member>
<member name="M:Poco.Any.op_Assign(Poco.Any!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\any.h" line="407">
Assignment operator for Any.
</member>
<member name="M:Poco.Any.empty" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\any.h" line="414">
Returns true if the Any is empty.
</member>
<member name="M:Poco.Any.type" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\any.h" line="420">
Returns the type information of the stored content.
If the Any is empty typeid(void) is returned.
It is recommended to always query an Any for its type info before
trying to extract data via an AnyCast/RefAnyCast.
</member>
<!-- Discarding badly formed XML document comment for member 'M:Poco.format(std.basic_string<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte>>!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Any!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Any!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)'. -->
<member name="M:Poco.format(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Any!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereference" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\format.h" line="124">
Appends the formatted string to result.
</member>
<member name="M:Poco.Net.StreamSocket.#ctor" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="36">
This class provides an interface to a
TCP stream socket.
</member>
<member name="M:Poco.Net.StreamSocket.#ctor(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="41">
Creates an unconnected stream socket.

Before sending or receiving data, the socket
must be connected with a call to connect().
</member>
<member name="M:Poco.Net.StreamSocket.#ctor(Poco.Net.AddressFamily.Family)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="47">
Creates a stream socket and connects it to
the socket specified by address.
</member>
<member name="M:Poco.Net.StreamSocket.#ctor(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="51">
Creates an unconnected stream socket
for the given address family.

This is useful if certain socket options
(like send and receive buffer) sizes, that must 
be set before connecting the socket, will be
set later on.
</member>
<member name="M:Poco.Net.StreamSocket.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="60">
Creates the StreamSocket with the SocketImpl
from another socket. The SocketImpl must be
a StreamSocketImpl, otherwise an InvalidArgumentException
will be thrown.
</member>
<member name="M:Poco.Net.StreamSocket.op_Assign(Poco.Net.Socket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="66">
Destroys the StreamSocket.
</member>
<member name="M:Poco.Net.StreamSocket.connect(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="69">
Assignment operator.

Releases the socket's SocketImpl and
attaches the SocketImpl from the other socket and
increments the reference count of the SocketImpl.	
</member>
<member name="M:Poco.Net.StreamSocket.connect(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="76">
Initializes the socket and establishes a connection to 
the TCP server at the given address.

Can also be used for UDP sockets. In this case, no
connection is established. Instead, incoming and outgoing
packets are restricted to the specified address.
</member>
<member name="M:Poco.Net.StreamSocket.connectNB(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="84">
Initializes the socket, sets the socket timeout and 
establishes a connection to the TCP server at the given address.
</member>
<member name="M:Poco.Net.StreamSocket.shutdownReceive" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="88">
Initializes the socket and establishes a connection to 
the TCP server at the given address. Prior to opening the
connection the socket is set to nonblocking mode.
</member>
<member name="M:Poco.Net.StreamSocket.shutdownSend" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="93">
Shuts down the receiving part of the socket connection.
</member>
<member name="M:Poco.Net.StreamSocket.shutdown" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="96">
Shuts down the sending part of the socket connection.
</member>
<member name="M:Poco.Net.StreamSocket.sendBytes(System.Void!System.Runtime.CompilerServices.IsConst*,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="99">
Shuts down both the receiving and the sending part
of the socket connection.
</member>
<member name="M:Poco.Net.StreamSocket.sendBytes(Poco.BasicFIFOBuffer&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="103">
Sends the contents of the given buffer through
the socket.

Returns the number of bytes sent, which may be
less than the number of bytes specified.

Certain socket implementations may also return a negative
value denoting a certain condition.
</member>
<member name="M:Poco.Net.StreamSocket.receiveBytes(System.Void*,System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="113">
Sends the contents of the given buffer through
the socket. FIFOBuffer has writable/readable transition
notifications which may be enabled to notify the caller when
the buffer transitions between empty, partially full and
full states.

Returns the number of bytes sent, which may be
less than the number of bytes specified.

Certain socket implementations may also return a negative
value denoting a certain condition.
</member>
<member name="M:Poco.Net.StreamSocket.receiveBytes(Poco.BasicFIFOBuffer&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="126">
Receives data from the socket and stores it
in buffer. Up to length bytes are received.

Returns the number of bytes received. 
A return value of 0 means a graceful shutdown 
of the connection from the peer.

Throws a TimeoutException if a receive timeout has
been set and nothing is received within that interval.
Throws a NetException (or a subclass) in case of other errors.
</member>
<member name="M:Poco.Net.StreamSocket.sendUrgent(System.Byte)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="138">
Receives data from the socket and stores it
in buffer. Up to length bytes are received. FIFOBuffer has 
writable/readable transition notifications which may be enabled 
to notify the caller when the buffer transitions between empty, 
partially full and full states.

Returns the number of bytes received. 
A return value of 0 means a graceful shutdown 
of the connection from the peer.

Throws a TimeoutException if a receive timeout has
been set and nothing is received within that interval.
Throws a NetException (or a subclass) in case of other errors.
</member>
<member name="M:Poco.Net.StreamSocket.#ctor(Poco.Net.SocketImpl*)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\streamsocket.h" line="153">
Sends one byte of urgent data through
the socket.

The data is sent with the MSG_OOB flag.

The preferred way for a socket to receive urgent data
is by enabling the SO_OOBINLINE option.
</member>
<member name="T:Poco.Net.HTTPSession" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="37">
HTTPSession implements basic HTTP session management
for both HTTP clients and HTTP servers.

HTTPSession implements buffering for HTTP connections, as well
as specific support for the various HTTP stream classes.

This class can not be instantiated. HTTPClientSession or
HTTPServerSession must be used instead.
</member>
<member name="M:Poco.Net.HTTPSession.getKeepAlive" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="48">
Sets the keep-alive flag for this session.

If the keep-alive flag is enabled, persistent
HTTP/1.1 connections are supported.
</member>
<member name="M:Poco.Net.HTTPSession.setTimeout(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="54">
Returns the value of the keep-alive flag for
this session.
</member>
<member name="M:Poco.Net.HTTPSession.setTimeout(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="58">
Sets the timeout for the HTTP session.
</member>
<member name="M:Poco.Net.HTTPSession.getTimeout" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="61">
Sets different timeouts for the HTTP session.
</member>
<member name="M:Poco.Net.HTTPSession.connected" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="64">
Returns the timeout for the HTTP session.
</member>
<member name="M:Poco.Net.HTTPSession.abort" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="67">
Returns true if the underlying socket is connected.
</member>
<member name="M:Poco.Net.HTTPSession.networkException" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="70">
Aborts a session in progress by shutting down
and closing the underlying socket.
</member>
<member name="M:Poco.Net.HTTPSession.attachSessionData(Poco.Any!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="74">
If sending or receiving data over the underlying
socket connection resulted in an exception, a
pointer to this exception is returned.

Otherwise, NULL is returned.
</member>
<member name="M:Poco.Net.HTTPSession.sessionData" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="81">
Allows to attach an application-specific data 
item to the session.

On the server side, this can be used to manage
data that must be maintained over the entire
lifetime of a persistent connection (that is,
multiple requests sent over the same connection).
</member>
<member name="M:Poco.Net.HTTPSession.socket" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="100">
Detaches the socket from the session.

The socket is returned, and a new, uninitialized socket is
attached to the session.
</member>
<member name="M:Poco.Net.HTTPSession.drainBuffer(Poco.Buffer&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="106">
Returns a reference to the underlying socket.
</member>
<member name="M:Poco.Net.HTTPSession.#ctor" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="109">
Copies all bytes remaining in the internal buffer to the
given Poco::Buffer, resizing it as necessary.

This is usually used together with detachSocket() to
obtain any data already read from the socket, but not
yet processed.
</member>
<member name="M:Poco.Net.HTTPSession.#ctor(Poco.Net.StreamSocket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="118">
Creates a HTTP session using an
unconnected stream socket.
</member>
<member name="M:Poco.Net.HTTPSession.#ctor(Poco.Net.StreamSocket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="122">
Creates a HTTP session using the
given socket. The session takes ownership
of the socket and closes it when it's no
longer used.
</member>
<member name="M:Poco.Net.HTTPSession.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="128">
Creates a HTTP session using the
given socket. The session takes ownership
of the socket and closes it when it's no
longer used.
</member>
<member name="M:Poco.Net.HTTPSession.get" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="134">
Destroys the HTTPSession and closes the
underlying socket.
</member>
<member name="M:Poco.Net.HTTPSession.peek" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="138">
Returns the next byte in the buffer.
Reads more data from the socket if there are
no bytes left in the buffer.
</member>
<member name="M:Poco.Net.HTTPSession.read(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte*,System.Int64)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="143">
Peeks at the next character in the buffer.
Reads more data from the socket if there are
no bytes left in the buffer.
</member>
<member name="M:Poco.Net.HTTPSession.write(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int64)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="148">
Reads up to length bytes.

If there is data in the buffer, this data
is returned. Otherwise, data is read from
the socket to avoid unnecessary buffering.
</member>
<member name="M:Poco.Net.HTTPSession.receive(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte*,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="155">
Writes data to the socket.
</member>
<member name="M:Poco.Net.HTTPSession.buffered" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="158">
Reads up to length bytes.
</member>
<member name="M:Poco.Net.HTTPSession.refill" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="161">
Returns the number of bytes in the buffer.
</member>
<member name="M:Poco.Net.HTTPSession.connect(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="164">
Refills the internal buffer.
</member>
<member name="M:Poco.Net.HTTPSession.attachSocket(Poco.Net.StreamSocket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="167">
Connects the underlying socket to the given address
and sets the socket's receive timeout.	
</member>
<member name="M:Poco.Net.HTTPSession.close" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="171">
Attaches a socket to the session, replacing the
previously attached socket.
</member>
<member name="M:Poco.Net.HTTPSession.setException(Poco.Exception!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="175">
Closes the underlying socket.
</member>
<member name="M:Poco.Net.HTTPSession.clearException" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpsession.h" line="178">
Stores a clone of the exception.
</member>
<!-- Discarding badly formed XML document comment for member 'T:Poco.Net.HTTPClientSession.ProxyConfig'. -->
<member name="F:Poco.Net.HTTPClientSession.ProxyConfig.port" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="76">
Proxy server host name or IP address.
</member>
<member name="F:Poco.Net.HTTPClientSession.ProxyConfig.username" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="78">
Proxy server TCP port.
</member>
<member name="F:Poco.Net.HTTPClientSession.ProxyConfig.password" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="80">
Proxy server username.
</member>
<member name="F:Poco.Net.HTTPClientSession.ProxyConfig.nonProxyHosts" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="82">
Proxy server password.
</member>
<member name="M:Poco.Net.HTTPClientSession.#ctor(Poco.Net.StreamSocket!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="90">
Creates an unconnected HTTPClientSession.
</member>
<member name="M:Poco.Net.HTTPClientSession.#ctor(Poco.Net.SocketAddress!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="93">
Creates a HTTPClientSession using the given socket.
The socket must not be connected. The session
takes ownership of the socket.
</member>
<member name="M:Poco.Net.HTTPClientSession.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="98">
Creates a HTTPClientSession using the given address.
</member>
<member name="M:Poco.Net.HTTPClientSession.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt16,Poco.Net.HTTPClientSession.ProxyConfig!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="101">
Creates a HTTPClientSession using the given host and port.
</member>
<member name="M:Poco.Net.HTTPClientSession.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="104">
Creates a HTTPClientSession using the given host, port and proxy configuration.
</member>
<member name="M:Poco.Net.HTTPClientSession.setHost(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="107">
Destroys the HTTPClientSession and closes
the underlying socket.
</member>
<member name="M:Poco.Net.HTTPClientSession.getHost" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="111">
Sets the host name of the target HTTP server.

The host must not be changed once there is an
open connection to the server.
</member>
<member name="M:Poco.Net.HTTPClientSession.setPort(System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="117">
Returns the host name of the target HTTP server.
</member>
<member name="M:Poco.Net.HTTPClientSession.getPort" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="120">
Sets the port number of the target HTTP server.

The port number must not be changed once there is an
open connection to the server.
</member>
<member name="M:Poco.Net.HTTPClientSession.setProxy(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="126">
Returns the port number of the target HTTP server.
</member>
<member name="M:Poco.Net.HTTPClientSession.setProxyHost(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="129">
Sets the proxy host name and port number.
</member>
<member name="M:Poco.Net.HTTPClientSession.setProxyPort(System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="132">
Sets the host name of the proxy server.
</member>
<member name="M:Poco.Net.HTTPClientSession.getProxyHost" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="135">
Sets the port number of the proxy server.
</member>
<member name="M:Poco.Net.HTTPClientSession.getProxyPort" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="138">
Returns the proxy host name.
</member>
<member name="M:Poco.Net.HTTPClientSession.setProxyCredentials(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="141">
Returns the proxy port number.
</member>
<member name="M:Poco.Net.HTTPClientSession.setProxyUsername(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="144">
Sets the username and password for proxy authentication.
Only Basic authentication is supported.
</member>
<member name="M:Poco.Net.HTTPClientSession.getProxyUsername" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="148">
Sets the username for proxy authentication.
Only Basic authentication is supported.
</member>
<member name="M:Poco.Net.HTTPClientSession.setProxyPassword(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="152">
Returns the username for proxy authentication.
</member>
<member name="M:Poco.Net.HTTPClientSession.getProxyPassword" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="155">
Sets the password for proxy authentication.	
Only Basic authentication is supported.
</member>
<member name="M:Poco.Net.HTTPClientSession.setProxyConfig(Poco.Net.HTTPClientSession.ProxyConfig!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="159">
Returns the password for proxy authentication.
</member>
<member name="M:Poco.Net.HTTPClientSession.getProxyConfig" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="162">
Sets the proxy configuration.
</member>
<member name="M:Poco.Net.HTTPClientSession.setGlobalProxyConfig(Poco.Net.HTTPClientSession.ProxyConfig!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="165">
Returns the proxy configuration.
</member>
<member name="M:Poco.Net.HTTPClientSession.getGlobalProxyConfig" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="168">
Sets the global proxy configuration.

The global proxy configuration is used by all HTTPClientSession
instances, unless a different proxy configuration is explicitly set.

Warning: Setting the global proxy configuration is not thread safe.
The global proxy configuration should be set at start up, before
the first HTTPClientSession instance is created.
</member>
<member name="M:Poco.Net.HTTPClientSession.setKeepAliveTimeout(Poco.Timespan!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="178">
Returns the global proxy configuration.
</member>
<member name="M:Poco.Net.HTTPClientSession.getKeepAliveTimeout" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="181">
Sets the connection timeout for HTTP connections.
</member>
<member name="M:Poco.Net.HTTPClientSession.sendRequest(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="184">
Returns the connection timeout for HTTP connections.
</member>
<member name="M:Poco.Net.HTTPClientSession.receiveResponse(Poco.Net.HTTPResponse*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="187">
Sends the header for the given HTTP request to
the server.

The HTTPClientSession will set the request's
Host and Keep-Alive headers accordingly.

The returned output stream can be used to write
the request body. The stream is valid until
receiveResponse() is called or the session
is destroyed.

In case a network or server failure happens
while writing the request body to the returned stream,
the stream state will change to bad or fail. In this
case, reset() should be called if the session will
be reused and persistent connections are enabled
to ensure a new connection will be set up
for the next request.
</member>
<member name="M:Poco.Net.HTTPClientSession.peekResponse(Poco.Net.HTTPResponse*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="207">
Receives the header for the response to the previous 
HTTP request.

The returned input stream can be used to read
the response body. The stream is valid until
sendRequest() is called or the session is
destroyed.

It must be ensured that the response stream
is fully consumed before sending a new request
and persistent connections are enabled. Otherwise,
the unread part of the response body may be treated as 
part of the next request's response header, resulting
in a Poco::Net::MessageException being thrown.

In case a network or server failure happens
while reading the response body from the returned stream,
the stream state will change to bad or fail. In this
case, reset() should be called if the session will
be reused and persistent connections are enabled
to ensure a new connection will be set up
for the next request.
</member>
<member name="M:Poco.Net.HTTPClientSession.reset" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="231">
If the request contains a "Expect: 100-continue" header,
(see HTTPRequest::setExpectContinue()) this method can be 
used to check whether the server has sent a 100 Continue response 
before continuing with the request, i.e. sending the request body,
after calling sendRequest().

Returns true if the server has responded with 100 Continue,
otherwise false. The HTTPResponse object contains the
response sent by the server. 

In any case, receiveResponse() must be called afterwards as well in
order to complete the request. The same HTTPResponse object
passed to peekResponse() must also be passed to receiveResponse().

This method should only be called if the request contains
a "Expect: 100-continue" header.
</member>
<member name="M:Poco.Net.HTTPClientSession.secure" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="249">
Resets the session and closes the socket.

The next request will initiate a new connection,
even if persistent connections are enabled.

This should be called whenever something went
wrong when sending a request (e.g., sendRequest()
or receiveResponse() throws an exception, or
the request or response stream changes into
fail or bad state, but not eof state).
</member>
<member name="M:Poco.Net.HTTPClientSession.bypassProxy" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="261">
Return true iff the session uses SSL or TLS,
or false otherwise.
</member>
<member name="M:Poco.Net.HTTPClientSession.write(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,System.Int64)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="275">
Connects the underlying socket to the HTTP server.
</member>
<member name="M:Poco.Net.HTTPClientSession.proxyRequestPrefix" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="278">
Tries to re-connect if keep-alive is on.
</member>
<member name="M:Poco.Net.HTTPClientSession.mustReconnect" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="281">
Returns the prefix prepended to the URI for proxy requests
(e.g., "http://myhost.com").
</member>
<member name="M:Poco.Net.HTTPClientSession.proxyAuthenticate(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="285">
Checks if we can reuse a persistent connection.
</member>
<member name="M:Poco.Net.HTTPClientSession.proxyAuthenticateImpl(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="288">
Sets the proxy credentials (Proxy-Authorization header), if
proxy username and password have been set.
</member>
<member name="M:Poco.Net.HTTPClientSession.proxyConnect" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="292">
Sets the proxy credentials (Proxy-Authorization header), if
proxy username and password have been set.
</member>
<member name="M:Poco.Net.HTTPClientSession.proxyTunnel" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="296">
Sends a CONNECT request to the proxy server and returns
a StreamSocket for the resulting connection.
</member>
<member name="F:Poco.Net.HTTPClientSession._host" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpclientsession.h" line="300">
Calls proxyConnect() and attaches the resulting StreamSocket
to the HTTPClientSession.
</member>
<member name="T:Poco.Ascii" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="30">
This class contains enumerations and static
utility functions for dealing with ASCII characters
and their properties.

The classification functions will also work if
non-ASCII character codes are passed to them,
but classification will only check for
ASCII characters.

This allows the classification methods to be used
on the single bytes of a UTF-8 string, without
causing assertions or inconsistent results (depending
upon the current locale) on bytes outside the ASCII range,
as may be produced by Ascii::isSpace(), etc.
</member>
<member name="T:Poco.Ascii.CharacterProperties" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="47">
ASCII character properties.
</member>
<member name="M:Poco.Ascii.hasSomeProperties(System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="62">
Return the ASCII character properties for the
character with the given ASCII value.

If the character is outside the ASCII range
(0 .. 127), 0 is returned.
</member>
<member name="M:Poco.Ascii.hasProperties(System.Int32,System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="69">
Returns true if the given character is
within the ASCII range and has at least one of 
the given properties.
</member>
<member name="M:Poco.Ascii.isAscii(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="74">
Returns true if the given character is
within the ASCII range and has all of 
the given properties.
</member>
<member name="M:Poco.Ascii.isSpace(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="79">
Returns true iff the given character code is within
the ASCII range (0 .. 127).
</member>
<member name="M:Poco.Ascii.isDigit(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="83">
Returns true iff the given character is a whitespace.
</member>
<member name="M:Poco.Ascii.isHexDigit(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="86">
Returns true iff the given character is a digit.
</member>
<member name="M:Poco.Ascii.isPunct(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="89">
Returns true iff the given character is a hexadecimal digit.
</member>
<member name="M:Poco.Ascii.isAlpha(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="92">
Returns true iff the given character is a punctuation character.
</member>
<member name="M:Poco.Ascii.isAlphaNumeric(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="95">
Returns true iff the given character is an alphabetic character.	
</member>
<member name="M:Poco.Ascii.isLower(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="98">
Returns true iff the given character is an alphabetic character.	
</member>
<member name="M:Poco.Ascii.isUpper(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="101">
Returns true iff the given character is a lowercase alphabetic
character.
</member>
<member name="M:Poco.Ascii.toLower(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="105">
Returns true iff the given character is an uppercase alphabetic
character.
</member>
<member name="M:Poco.Ascii.toUpper(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="109">
If the given character is an uppercase character,
return its lowercase counterpart, otherwise return
the character.
</member>
<member name="F:Poco.Ascii.CHARACTER_PROPERTIES" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\ascii.h" line="114">
If the given character is a lowercase character,
return its uppercase counterpart, otherwise return
the character.
</member>
<member name="T:Poco.CILess" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\string.h" line="704">
Case-insensitive less-than functor; useful for standard maps
and sets with std::strings keys and case-insensitive ordering
requirement.
</member>
<member name="T:Poco.Net.NameValueCollection" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="34">
A collection of name-value pairs that are used in
various internet protocols like HTTP and SMTP.

The name is case-insensitive.

There can be more than one name-value pair with the 
same name.
</member>
<member name="M:Poco.Net.NameValueCollection.#ctor(Poco.Net.NameValueCollection!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="48">
Creates an empty NameValueCollection.
</member>
<member name="M:Poco.Net.NameValueCollection.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="51">
Creates a NameValueCollection by copying another one.
</member>
<member name="M:Poco.Net.NameValueCollection.op_Assign(Poco.Net.NameValueCollection!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="54">
Destroys the NameValueCollection.
</member>
<member name="M:Poco.Net.NameValueCollection.swap(Poco.Net.NameValueCollection*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="57">
Assigns the name-value pairs of another NameValueCollection to this one.
</member>
<member name="M:Poco.Net.NameValueCollection.op_Subscript(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="60">
Swaps the NameValueCollection with another one.
</member>
<member name="M:Poco.Net.NameValueCollection.set(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="63">
Returns the value of the (first) name-value pair with the given name.

Throws a NotFoundException if the name-value pair does not exist.
</member>
<member name="M:Poco.Net.NameValueCollection.add(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="68">
Sets the value of the (first) name-value pair with the given name.
</member>
<member name="M:Poco.Net.NameValueCollection.get(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="71">
Adds a new name-value pair with the given name and value.
</member>
<member name="M:Poco.Net.NameValueCollection.get(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="74">
Returns the value of the first name-value pair with the given name.

Throws a NotFoundException if the name-value pair does not exist.
</member>
<member name="M:Poco.Net.NameValueCollection.has(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="79">
Returns the value of the first name-value pair with the given name.
If no value with the given name has been found, the defaultValue is returned.
</member>
<member name="M:Poco.Net.NameValueCollection.find(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="83">
Returns true if there is at least one name-value pair
with the given name.
</member>
<member name="M:Poco.Net.NameValueCollection.begin" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="87">
Returns an iterator pointing to the first name-value pair
with the given name.
</member>
<member name="M:Poco.Net.NameValueCollection.end" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="91">
Returns an iterator pointing to the begin of
the name-value pair collection.
</member>
<member name="M:Poco.Net.NameValueCollection.empty" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="95">
Returns an iterator pointing to the end of 
the name-value pair collection.
</member>
<member name="M:Poco.Net.NameValueCollection.size" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="99">
Returns true iff the header does not have any content.
</member>
<member name="M:Poco.Net.NameValueCollection.erase(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="102">
Returns the number of name-value pairs in the
collection.
</member>
<member name="M:Poco.Net.NameValueCollection.clear" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="106">
Removes all name-value pairs with the given name.
</member>
<member name="F:Poco.Net.NameValueCollection._map" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\namevaluecollection.h" line="109">
Removes all name-value pairs and their values.
</member>
<member name="M:Poco.Net.MessageHeader.#ctor" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="35">
A collection of name-value pairs that are used in
various internet protocols like HTTP and SMTP.

The name is case-insensitive.

There can be more than one name-value pair with the 
same name.

MessageHeader supports writing and reading the
header data in RFC 2822 format.

The maximum number of fields can be restricted
by calling setFieldLimit(). This is useful to
defend against certain kinds of denial-of-service
attacks. The limit is only enforced when parsing
header fields from a stream, not when programmatically
adding them. The default limit is 100.
</member>
<member name="M:Poco.Net.MessageHeader.#ctor(Poco.Net.MessageHeader!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="55">
Creates the MessageHeader.
</member>
<member name="M:Poco.Net.MessageHeader.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="58">
Creates the MessageHeader by copying
another one.
</member>
<member name="M:Poco.Net.MessageHeader.op_Assign(Poco.Net.MessageHeader!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="62">
Destroys the MessageHeader.
</member>
<member name="M:Poco.Net.MessageHeader.write(std.basic_ostream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="65">
Assigns the content of another MessageHeader.
</member>
<member name="M:Poco.Net.MessageHeader.read(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="68">
Writes the message header to the given output stream.

The format is one name-value pair per line, with
name and value separated by a colon and lines
delimited by a carriage return and a linefeed 
character. See RFC 2822 for details.
</member>
<member name="M:Poco.Net.MessageHeader.getFieldLimit" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="76">
Reads the message header from the given input stream.

See write() for the expected format.
Also supported is folding of field content, according
to section 2.2.3 of RFC 2822.

Reading stops at the first empty line (a line only
containing \r\n or \n), as well as at the end of
the stream.

Some basic sanity checking of the input stream is
performed.

Throws a MessageException if the input stream is
malformed.
</member>
<member name="M:Poco.Net.MessageHeader.setFieldLimit(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="93">
Returns the maximum number of header fields
allowed.

See setFieldLimit() for more information.
</member>
<member name="M:Poco.Net.MessageHeader.hasToken(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="99">
Sets the maximum number of header fields
allowed. This limit is used to defend certain
kinds of denial-of-service attacks.
Specify 0 for unlimited (not recommended).

The default limit is 100.
</member>
<member name="M:Poco.Net.MessageHeader.splitElements(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.vector&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.allocator&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="107">
Returns true iff the field with the given fieldName contains
the given token. Tokens in a header field are expected to be
comma-separated and are case insensitive.
</member>
<member name="M:Poco.Net.MessageHeader.splitParameters(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.NameValueCollection*!System.Runtime.CompilerServices.IsImplicitlyDere" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="112">
Splits the given string into separate elements. Elements are expected
to be separated by commas.

For example, the string 
  text/plain; q=0.5, text/html, text/x-dvi; q=0.8
is split into the elements
  text/plain; q=0.5
  text/html
  text/x-dvi; q=0.8

Commas enclosed in double quotes do not split elements.

If ignoreEmpty is true, empty elements are not returned.
</member>
<member name="M:Poco.Net.MessageHeader.splitParameters(std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.NameValueCollection*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="127">
Splits the given string into a value and a collection of parameters.
Parameters are expected to be separated by semicolons.

Enclosing quotes of parameter values are removed.

For example, the string
  multipart/mixed; boundary="MIME_boundary_01234567"
is split into the value
  multipart/mixed
and the parameter
  boundary -&gt; MIME_boundary_01234567
</member>
<member name="M:Poco.Net.MessageHeader.quote(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="140">
Splits the given string into a collection of parameters.
Parameters are expected to be separated by semicolons.

Enclosing quotes of parameter values are removed.
</member>
<member name="M:Poco.Net.MessageHeader.decodeRFC2047(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedB" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="146">
Checks if the value must be quoted. If so, the value is
appended to result, enclosed in double-quotes.
Otherwise, the value is appended to result as-is.
</member>
<member name="T:Poco.Net.MessageHeader.Limits" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\messageheader.h" line="152">
Decode RFC2047 string.
Limits for basic sanity checks when reading a header
</member>
<member name="M:Poco.Net.HTTPMessage.setVersion(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="35">
The base class for HTTPRequest and HTTPResponse.

Defines the common properties of all HTTP messages.
These are version, content length, content type
and transfer encoding.
</member>
<member name="M:Poco.Net.HTTPMessage.getVersion" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="43">
Sets the HTTP version for this message.
</member>
<member name="M:Poco.Net.HTTPMessage.setContentLength(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="46">
Returns the HTTP version for this message.
</member>
<member name="M:Poco.Net.HTTPMessage.getContentLength" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="49">
Sets the Content-Length header.

If length is UNKNOWN_CONTENT_LENGTH, removes
the Content-Length header.
</member>
<member name="M:Poco.Net.HTTPMessage.setContentLength64(System.Int64)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="55">
Returns the content length for this message,
which may be UNKNOWN_CONTENT_LENGTH if
no Content-Length header is present.
</member>
<member name="M:Poco.Net.HTTPMessage.getContentLength64" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="61">
Sets the Content-Length header.

If length is UNKNOWN_CONTENT_LENGTH, removes
the Content-Length header.

In contrast to setContentLength(), this method takes
a 64-bit integer as content length.
</member>
<member name="M:Poco.Net.HTTPMessage.hasContentLength" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="70">
Returns the content length for this message,
which may be UNKNOWN_CONTENT_LENGTH if
no Content-Length header is present.

In contrast to getContentLength(), this method
always returns a 64-bit integer for content length.
</member>
<member name="M:Poco.Net.HTTPMessage.setTransferEncoding(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="79">
Returns true iff a Content-Length header is present.
</member>
<member name="M:Poco.Net.HTTPMessage.getTransferEncoding" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="82">
Sets the transfer encoding for this message.

The value should be either IDENTITY_TRANSFER_CODING
or CHUNKED_TRANSFER_CODING.
</member>
<member name="M:Poco.Net.HTTPMessage.setChunkedTransferEncoding(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="88">
Returns the transfer encoding used for this
message.

Normally, this is the value of the Transfer-Encoding
header field. If no such field is present,
returns IDENTITY_TRANSFER_CODING.
</member>
<member name="M:Poco.Net.HTTPMessage.getChunkedTransferEncoding" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="96">
If flag is true, sets the Transfer-Encoding header to
chunked. Otherwise, removes the Transfer-Encoding
header.
</member>
<member name="M:Poco.Net.HTTPMessage.setContentType(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="101">
Returns true if the Transfer-Encoding header is set
and its value is chunked.
</member>
<member name="M:Poco.Net.HTTPMessage.setContentType(Poco.Net.MediaType!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="105">
Sets the content type for this message.

Specify NO_CONTENT_TYPE to remove the
Content-Type header.
</member>
<member name="M:Poco.Net.HTTPMessage.getContentType" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="111">
Sets the content type for this message.
</member>
<member name="M:Poco.Net.HTTPMessage.setKeepAlive(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="114">
Returns the content type for this message.

If no Content-Type header is present, 
returns UNKNOWN_CONTENT_TYPE.	
</member>
<member name="M:Poco.Net.HTTPMessage.getKeepAlive" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="120">
Sets the value of the Connection header field.

The value is set to "Keep-Alive" if keepAlive is
true, or to "Close" otherwise.
</member>
<member name="F:Poco.Net.HTTPMessage.HTTP_1_0" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="126">
Returns true if
  * the message has a Connection header field and its value is "Keep-Alive"
  * the message is a HTTP/1.1 message and not Connection header is set
Returns false otherwise.
</member>
<member name="M:Poco.Net.HTTPMessage.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="152">
Creates the HTTPMessage with version HTTP/1.0.
</member>
<member name="M:Poco.Net.HTTPMessage.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="155">
Creates the HTTPMessage and sets
the version.
</member>
<member name="M:Poco.Net.HTTPMessage.#ctor(Poco.Net.HTTPMessage!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpmessage.h" line="159">
Destroys the HTTPMessage.
</member>
<member name="M:Poco.Net.HTTPRequest.#ctor" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="32">
This class encapsulates an HTTP request
message.

In addition to the properties common to
all HTTP messages, a HTTP request has
a method (e.g. GET, HEAD, POST, etc.) and
a request URI.
</member>
<member name="M:Poco.Net.HTTPRequest.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="42">
Creates a GET / HTTP/1.0 HTTP request.
</member>
<member name="M:Poco.Net.HTTPRequest.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="45">
Creates a GET / HTTP/1.x request with
the given version (HTTP/1.0 or HTTP/1.1).
</member>
<member name="M:Poco.Net.HTTPRequest.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.Compi" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="49">
Creates a HTTP/1.0 request with the given method and URI.
</member>
<member name="M:Poco.Net.HTTPRequest.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="52">
Creates a HTTP request with the given method, URI and version.
</member>
<member name="M:Poco.Net.HTTPRequest.setMethod(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="55">
Destroys the HTTPRequest.
</member>
<member name="M:Poco.Net.HTTPRequest.getMethod" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="58">
Sets the method.
</member>
<member name="M:Poco.Net.HTTPRequest.setURI(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="61">
Returns the method.
</member>
<member name="M:Poco.Net.HTTPRequest.getURI" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="64">
Sets the request URI.
</member>
<member name="M:Poco.Net.HTTPRequest.setHost(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="67">
Returns the request URI.
</member>
<member name="M:Poco.Net.HTTPRequest.setHost(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="70">
Sets the value of the Host header field.
</member>
<member name="M:Poco.Net.HTTPRequest.getHost" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="73">
Sets the value of the Host header field.

If the given port number is a non-standard
port number (other than 80 or 443), it is
included in the Host header field.
</member>
<member name="M:Poco.Net.HTTPRequest.setCookies(Poco.Net.NameValueCollection!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="80">
Returns the value of the Host header field.

Throws a NotFoundException if the request
does not have a Host header field.
</member>
<member name="M:Poco.Net.HTTPRequest.getCookies(Poco.Net.NameValueCollection*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="86">
Adds a Cookie header with the names and
values from cookies.
</member>
<member name="M:Poco.Net.HTTPRequest.hasCredentials" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="90">
Fills cookies with the cookies extracted
from the Cookie headers in the request.
</member>
<member name="M:Poco.Net.HTTPRequest.getCredentials(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="94">
Returns true iff the request contains authentication
information in the form of an Authorization header.
</member>
<member name="M:Poco.Net.HTTPRequest.setCredentials(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="98">
Returns the authentication scheme and additional authentication
information contained in this request.

Throws a NotAuthenticatedException if no authentication information
is contained in the request.
</member>
<member name="M:Poco.Net.HTTPRequest.getExpectContinue" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="105">
Sets the authentication scheme and information for
this request.
</member>
<member name="M:Poco.Net.HTTPRequest.setExpectContinue(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="109">
Returns true if the request contains an
"Expect: 100-continue" header.
</member>
<member name="M:Poco.Net.HTTPRequest.hasProxyCredentials" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="113">
Adds a "Expect: 100-continue" header to the request if
expectContinue is true, otherwise removes the Expect header.
</member>
<member name="M:Poco.Net.HTTPRequest.getProxyCredentials(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="117">
Returns true iff the request contains proxy authentication
information in the form of an Proxy-Authorization header.
</member>
<member name="M:Poco.Net.HTTPRequest.setProxyCredentials(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="121">
Returns the proxy authentication scheme and additional proxy authentication
information contained in this request.

Throws a NotAuthenticatedException if no proxy authentication information
is contained in the request.
</member>
<member name="M:Poco.Net.HTTPRequest.write(std.basic_ostream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="128">
Sets the proxy authentication scheme and information for
this request.
</member>
<member name="M:Poco.Net.HTTPRequest.read(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="132">
Writes the HTTP request to the given
output stream.
</member>
<member name="F:Poco.Net.HTTPRequest.HTTP_GET" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="136">
Reads the HTTP request from the
given input stream.
</member>
<member name="M:Poco.Net.HTTPRequest.setCredentials(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runt" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="158">
Returns the authentication scheme and additional authentication
information contained in the given header of request.

Throws a NotAuthenticatedException if no authentication information
is contained in the request.
</member>
<member name="T:Poco.Net.HTTPRequest.Limits" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httprequest.h" line="165">
Writes the authentication scheme and information for
this request to the given header.
</member>
<member name="T:Poco.Net.HTTPCookie" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="34">
This class represents a HTTP Cookie.

A cookie is a small amount of information sent by a Web 
server to a Web browser, saved by the browser, and later sent back 
to the server. A cookie's value can uniquely identify a client, so 
cookies are commonly used for session management.

A cookie has a name, a single value, and optional attributes such 
as a comment, path and domain qualifiers, a maximum age, and a 
version number.

This class supports both the Version 0 (by Netscape) and Version 1 
(by RFC 2109) cookie specifications. By default, cookies are created 
using Version 0 to ensure the best interoperability.
</member>
<member name="M:Poco.Net.HTTPCookie.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="51">
Creates an empty HTTPCookie.
</member>
<member name="M:Poco.Net.HTTPCookie.#ctor(Poco.Net.NameValueCollection!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="54">
Creates a cookie with the given name.	
The cookie never expires.
</member>
<member name="M:Poco.Net.HTTPCookie.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="58">
Creates a cookie from the given NameValueCollection.
</member>
<member name="M:Poco.Net.HTTPCookie.#ctor(Poco.Net.HTTPCookie!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="61">
Creates a cookie with the given name and value.
The cookie never expires.

Note: If value contains whitespace or non-alphanumeric
characters, the value should be escaped by calling escape()
before passing it to the constructor.
</member>
<member name="M:Poco.Net.HTTPCookie.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="69">
Creates the HTTPCookie by copying another one.
</member>
<member name="M:Poco.Net.HTTPCookie.op_Assign(Poco.Net.HTTPCookie!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="72">
Destroys the HTTPCookie.
</member>
<member name="M:Poco.Net.HTTPCookie.setVersion(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="75">
Assigns a cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getVersion" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="78">
Sets the version of the cookie.

Version must be either 0 (denoting a Netscape cookie)
or 1 (denoting a RFC 2109 cookie).
</member>
<member name="M:Poco.Net.HTTPCookie.setName(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="84">
Returns the version of the cookie, which is
either 0 or 1.	
</member>
<member name="M:Poco.Net.HTTPCookie.getName" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="88">
Sets the name of the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.setValue(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="91">
Returns the name of the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getValue" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="94">
Sets the value of the cookie.

According to the cookie specification, the
size of the value should not exceed 4 Kbytes.

Note: If value contains whitespace or non-alphanumeric
characters, the value should be escaped by calling escape()
prior to passing it to setName().
</member>
<member name="M:Poco.Net.HTTPCookie.setComment(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="104">
Returns the value of the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getComment" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="107">
Sets the comment for the cookie.

Comments are only supported for version 1 cookies.
</member>
<member name="M:Poco.Net.HTTPCookie.setDomain(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="112">
Returns the comment for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getDomain" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="115">
Sets the domain for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.setPath(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="118">
Returns the domain for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.setPriority(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="121">
Sets the path for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getPath" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="124">
Sets the priority for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getPriority" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="127">
Returns the path for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.setSecure(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="130">
Returns the priority for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getSecure" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="133">
Sets the value of the secure flag for
the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.setMaxAge(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="137">
Returns the value of the secure flag
for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getMaxAge" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="141">
Sets the maximum age in seconds for
the cookie.

A value of -1 (default) causes the cookie 
to become a session cookie, which will
be deleted when the browser window
is closed.

A value of 0 deletes the cookie on
the client.
</member>
<member name="M:Poco.Net.HTTPCookie.setHttpOnly(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="153">
Returns the maximum age in seconds for
the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.getHttpOnly" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="157">
Sets the HttpOnly flag for the cookie.
</member>
<member name="M:Poco.Net.HTTPCookie.toString" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="160">
Returns true iff the cookie's HttpOnly flag is set.
</member>
<member name="M:Poco.Net.HTTPCookie.escape(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="163">
Returns a string representation of the cookie,
suitable for use in a Set-Cookie header.
</member>
<!-- Discarding badly formed XML document comment for member 'M:Poco.Net.HTTPCookie.unescape(std.basic_string<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte>>!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)'. -->
<member name="F:Poco.Net.HTTPCookie._version" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpcookie.h" line="190">
Unescapes the given string by replacing all
escape sequences in the form %xx with the
respective characters.
</member>
<member name="T:Poco.Net.HTTPResponse.HTTPStatus" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="38">
This class encapsulates an HTTP response
message.

In addition to the properties common to
all HTTP messages, a HTTP response has
status code and a reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.#ctor(Poco.Net.HTTPResponse.HTTPStatus,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="117">
Creates the HTTPResponse with OK status.
</member>
<member name="M:Poco.Net.HTTPResponse.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.HTTPResponse.HTTPStatus,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="120">
Creates the HTTPResponse with the given status
and reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.#ctor(Poco.Net.HTTPResponse.HTTPStatus)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="124">
Creates the HTTPResponse with the given version, status
and reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.HTTPResponse.HTTPStatus)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="128">
Creates the HTTPResponse with the given status
an an appropriate reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="132">
Creates the HTTPResponse with the given version, status
an an appropriate reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.setStatus(Poco.Net.HTTPResponse.HTTPStatus)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="136">
Destroys the HTTPResponse.
</member>
<member name="M:Poco.Net.HTTPResponse.getStatus" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="139">
Sets the HTTP status code.

Does not change the reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.setStatus(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="144">
Returns the HTTP status code.
</member>
<member name="M:Poco.Net.HTTPResponse.setReason(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="147">
Sets the HTTP status code.

The string must contain a valid
HTTP numerical status code.
</member>
<member name="M:Poco.Net.HTTPResponse.getReason" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="153">
Sets the HTTP reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.setStatusAndReason(Poco.Net.HTTPResponse.HTTPStatus,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="156">
Returns the HTTP reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.setStatusAndReason(Poco.Net.HTTPResponse.HTTPStatus)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="159">
Sets the HTTP status code and reason phrase.
</member>
<member name="M:Poco.Net.HTTPResponse.setDate(Poco.Timestamp!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="162">
Sets the HTTP status code and reason phrase.

The reason phrase is set according to the status code.
</member>
<member name="M:Poco.Net.HTTPResponse.getDate" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="167">
Sets the Date header to the given date/time value.
</member>
<member name="M:Poco.Net.HTTPResponse.addCookie(Poco.Net.HTTPCookie!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="170">
Returns the value of the Date header.
</member>
<member name="M:Poco.Net.HTTPResponse.getCookies(std.vector&lt;Poco.Net.HTTPCookie,std.allocator&lt;Poco.Net.HTTPCookie&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="173">
Adds the cookie to the response by
adding a Set-Cookie header.
</member>
<member name="M:Poco.Net.HTTPResponse.write(std.basic_ostream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="177">
Returns a vector with all the cookies
set in the response header.

May throw an exception in case of a malformed
Set-Cookie header.
</member>
<member name="M:Poco.Net.HTTPResponse.read(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="184">
Writes the HTTP response to the given
output stream.
</member>
<member name="M:Poco.Net.HTTPResponse.getReasonForStatus(Poco.Net.HTTPResponse.HTTPStatus)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="188">
Reads the HTTP response from the
given input stream.

100 Continue responses are ignored.
</member>
<member name="F:Poco.Net.HTTPResponse.HTTP_REASON_CONTINUE" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpresponse.h" line="194">
Returns an appropriate reason phrase
for the given status code.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.#ctor" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="36">
Collection of name-value pairs of HTTP authentication header (i.e.
"realm", "qop", "nonce" in case of digest authentication header).
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="41">
Creates an empty authentication parameters collection.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.#ctor(Poco.Net.HTTPRequest!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="44">
See fromAuthInfo() documentation.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.#ctor(Poco.Net.HTTPResponse!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="47">
See fromRequest() documentation.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="50">
See fromResponse() documentation.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.op_Assign(Poco.Net.HTTPAuthenticationParams!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="53">
Destroys the HTTPAuthenticationParams.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.fromAuthInfo(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="56">
Assigns the content of another HTTPAuthenticationParams.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.fromRequest(Poco.Net.HTTPRequest!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="59">
Creates an HTTPAuthenticationParams by parsing authentication
information.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.fromResponse(Poco.Net.HTTPResponse!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="63">
Extracts authentication information from the request and creates
HTTPAuthenticationParams by parsing it.

Throws a NotAuthenticatedException if no authentication
information is contained in request.
Throws a InvalidArgumentException if authentication scheme is
unknown or invalid.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.setRealm(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="72">
Extracts authentication information from the response and creates
HTTPAuthenticationParams by parsing it.

Throws a NotAuthenticatedException if no authentication
information is contained in response.
Throws a InvalidArgumentException if authentication scheme is
unknown or invalid.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.getRealm" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="81">
Sets the "realm" parameter to the provided string.
</member>
<member name="M:Poco.Net.HTTPAuthenticationParams.toString" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="84">
Returns value of the "realm" parameter.

Throws NotFoundException is there is no "realm" set in the
HTTPAuthenticationParams.
</member>
<member name="F:Poco.Net.HTTPAuthenticationParams.REALM" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpauthenticationparams.h" line="90">
Formats the HTTPAuthenticationParams for inclusion in HTTP
request or response authentication header.
</member>
<member name="T:Poco.Net.HTTPDigestCredentials" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="38">
This is a utility class for working with
HTTP Digest Authentication in HTTPRequest
objects.

Note: currently, no qop or qop=auth is
supported only.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="47">
Creates an empty HTTPDigestCredentials object.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.Dispose" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="50">
Creates a HTTPDigestCredentials object with the given username and password.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.reset" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="53">
Destroys the HTTPDigestCredentials.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.setUsername(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="56">
Resets the HTTPDigestCredentials object to a clean state.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.getUsername" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="59">
Sets the username.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.setPassword(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="62">
Returns the username.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.getPassword" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="65">
Sets the password.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.authenticate(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.HTTPResponse!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="68">
Returns the password.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.authenticate(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.HTTPAuthenticationParams!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="71">
Parses WWW-Authenticate header of the HTTPResponse, initializes
internal state, and adds authentication information to the given HTTPRequest.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.updateAuthInfo(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="75">
Initializes internal state according to information from the
HTTPAuthenticationParams of the response, and adds authentication
information to the given HTTPRequest.

Throws InvalidArgumentException if HTTPAuthenticationParams is
invalid or some required parameter is missing.
Throws NotImplementedException in case of unsupported digest
algorithm or quality of protection method.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.proxyAuthenticate(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.HTTPResponse!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="85">
Updates internal state and adds authentication information to
the given HTTPRequest.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.proxyAuthenticate(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.HTTPAuthenticationParams!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="89">
Parses Proxy-Authenticate header of the HTTPResponse, initializes
internal state, and adds proxy authentication information to the given HTTPRequest.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.updateProxyAuthInfo(Poco.Net.HTTPRequest*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="93">
Initializes internal state according to information from the
HTTPAuthenticationParams of the response, and adds proxy authentication
information to the given HTTPRequest.

Throws InvalidArgumentException if HTTPAuthenticationParams is
invalid or some required parameter is missing.
Throws NotImplementedException in case of unsupported digest
algorithm or quality of protection method.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.verifyAuthInfo(Poco.Net.HTTPRequest!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="103">
Updates internal state and adds proxy authentication information to
the given HTTPRequest.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.verifyAuthParams(Poco.Net.HTTPRequest!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Net.HTTPAuthenticationParams!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="107">
Verifies the digest authentication information in the given HTTPRequest
by recomputing the response and comparing it with what's in the request.

Note: This method creates a HTTPAuthenticationParams object from the request
and calls verifyAuthParams() with request and params.
</member>
<member name="M:Poco.Net.HTTPDigestCredentials.createNonce" decl="true" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="114">
Verifies the digest authentication information in the given HTTPRequest
and HTTPAuthenticationParams by recomputing the response and comparing 
it with what's in the request.
</member>
<member name="F:Poco.Net.HTTPDigestCredentials.SCHEME" decl="false" source="f:\projects\trader\deps\poco\net\include\poco\net\httpdigestcredentials.h" line="119">
Creates a random nonce string.
</member>
<member name="T:Poco.StreamCopier" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\streamcopier.h" line="33">
This class provides static methods to copy the contents from one stream
into another.
</member>
<member name="M:Poco.StreamCopier.copyStream64(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_ostream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\streamcopier.h" line="38">
Writes all bytes readable from istr to ostr, using an internal buffer.

Returns the number of bytes copied.
</member>
<member name="M:Poco.StreamCopier.copyStreamUnbuffered(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_ostream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\streamcopier.h" line="44">
Writes all bytes readable from istr to ostr, using an internal buffer.

Returns the number of bytes copied as a 64-bit unsigned integer.

Note: the only difference to copyStream() is that a 64-bit unsigned
integer is used to count the number of bytes copied.
</member>
<member name="M:Poco.StreamCopier.copyStreamUnbuffered64(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_ostream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\streamcopier.h" line="53">
Writes all bytes readable from istr to ostr.

Returns the number of bytes copied.
</member>
<member name="M:Poco.StreamCopier.copyToString(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\streamcopier.h" line="59">
Writes all bytes readable from istr to ostr.

Returns the number of bytes copied as a 64-bit unsigned integer.

Note: the only difference to copyStreamUnbuffered() is that a 64-bit unsigned
integer is used to count the number of bytes copied.
</member>
<member name="M:Poco.StreamCopier.copyToString64(std.basic_istream&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte}&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.UInt64)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\streamcopier.h" line="68">
Appends all bytes readable from istr to the given string, using an internal buffer.

Returns the number of bytes copied.
</member>
<member name="M:Poco.NullStreamBuf.#ctor" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="33">
This stream buffer discards all characters written to it.
Any read operation immediately yields EOF.
</member>
<member name="M:Poco.NullStreamBuf.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="38">
Creates a NullStreamBuf.
</member>
<member name="M:Poco.NullStreamBuf.readFromDevice" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="41">
Destroys the NullStreamBuf.
</member>
<member name="M:Poco.NullIOS.#ctor" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="50">
The base class for NullInputStream and NullOutputStream.

This class is needed to ensure the correct initialization
order of the stream buffer and base classes.
</member>
<member name="M:Poco.NullInputStream.#ctor" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="65">
Any read operation from this stream immediately
yields EOF.
</member>
<member name="M:Poco.NullInputStream.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="70">
Creates the NullInputStream.
</member>
<member name="M:Poco.NullOutputStream.#ctor" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="78">
This stream discards all characters written to it.
</member>
<member name="M:Poco.NullOutputStream.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\nullstream.h" line="82">
Creates the NullOutputStream.
</member>
<member name="T:Poco.Path" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="31">
This class represents filesystem paths in a 
platform-independent manner.
Unix, Windows and OpenVMS all use a different
syntax for filesystem paths.
This class can work with all three formats.
A path is made up of an optional node name
(only Windows and OpenVMS), an optional
device name (also only Windows and OpenVMS),
a list of directory names and an optional
filename.
</member>
<member name="M:Poco.Path.#ctor(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="56">
Creates an empty relative path.
</member>
<member name="M:Poco.Path.#ctor(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="59">
Creates an empty absolute or relative path.
</member>
<member name="M:Poco.Path.#ctor(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*,Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="62">
Creates a path from a string.
</member>
<member name="M:Poco.Path.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="65">
Creates a path from a string.
</member>
<member name="M:Poco.Path.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="68">
Creates a path from a string.
</member>
<member name="M:Poco.Path.#ctor(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="71">
Creates a path from a string.
</member>
<member name="M:Poco.Path.#ctor(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="74">
Copy constructor
</member>
<member name="M:Poco.Path.#ctor(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="77">
Creates a path from a parent path and a filename.
The parent path is expected to reference a directory.
</member>
<member name="M:Poco.Path.#ctor(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="81">
Creates a path from a parent path and a filename.
The parent path is expected to reference a directory.
</member>
<member name="M:Poco.Path.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="85">
Creates a path from a parent path and a relative path.
The parent path is expected to reference a directory.
The relative path is appended to the parent path.
</member>
<member name="M:Poco.Path.op_Assign(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="90">
Destroys the Path.
</member>
<member name="M:Poco.Path.op_Assign(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="93">
Assignment operator.
</member>
<member name="M:Poco.Path.op_Assign(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="96">
Assigns a string containing a path in native format.
</member>
<member name="M:Poco.Path.swap(Poco.Path*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="99">
Assigns a string containing a path in native format.
</member>
<member name="M:Poco.Path.assign(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="102">
Swaps the path with another one.
</member>
<member name="M:Poco.Path.assign(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="105">
Assigns a string containing a path in native format.
</member>
<member name="M:Poco.Path.assign(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="108">
Assigns a string containing a path.
</member>
<member name="M:Poco.Path.assign(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="111">
Assigns the given path.
</member>
<member name="M:Poco.Path.toString" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="114">
Assigns a string containing a path.
</member>
<member name="M:Poco.Path.toString(Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="117">
Returns a string containing the path in native format.
</member>
<member name="M:Poco.Path.parse(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="120">
Returns a string containing the path in the given format.
</member>
<member name="M:Poco.Path.parse(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="123">
Same as assign().
</member>
<member name="M:Poco.Path.tryParse(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="126">
Assigns a string containing a path.
</member>
<member name="M:Poco.Path.tryParse(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="129">
Tries to interpret the given string as a path
in native format.
If the path is syntactically valid, assigns the
path and returns true. Otherwise leaves the 
object unchanged and returns false.
</member>
<member name="M:Poco.Path.parseDirectory(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="136">
Tries to interpret the given string as a path,
according to the given style.
If the path is syntactically valid, assigns the
path and returns true. Otherwise leaves the
object unchanged and returns false.
</member>
<member name="M:Poco.Path.parseDirectory(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="143">
The resulting path always refers to a directory and
the filename part is empty.
</member>
<member name="M:Poco.Path.makeDirectory" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="147">
The resulting path always refers to a directory and
the filename part is empty.
</member>
<member name="M:Poco.Path.makeFile" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="151">
If the path contains a filename, the filename is appended
to the directory list and cleared. Thus the resulting path
always refers to a directory.
</member>
<member name="M:Poco.Path.makeParent" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="156">
If the path contains no filename, the last directory
becomes the filename.
</member>
<member name="M:Poco.Path.makeAbsolute" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="160">
Makes the path refer to its parent.
</member>
<member name="M:Poco.Path.makeAbsolute(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="163">
Makes the path absolute if it is relative.
The current working directory is taken as base directory.
</member>
<member name="M:Poco.Path.append(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="167">
Makes the path absolute if it is relative.
The given path is taken as base. 
</member>
<member name="M:Poco.Path.resolve(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="171">
Appends the given path.
</member>
<member name="M:Poco.Path.isAbsolute" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="174">
Resolves the given path against the current one.

If the given path is absolute, it replaces the current one.
Otherwise, the relative path is appended to the current path.
</member>
<member name="M:Poco.Path.isRelative" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="180">
Returns true iff the path is absolute.
</member>
<member name="M:Poco.Path.isDirectory" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="183">
Returns true iff the path is relative.
</member>
<member name="M:Poco.Path.isFile" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="186">
Returns true iff the path references a directory
(the filename part is empty).
</member>
<member name="M:Poco.Path.setNode(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="190">
Returns true iff the path references a file
(the filename part is not empty).
</member>
<member name="M:Poco.Path.getNode" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="194">
Sets the node name.
Setting a non-empty node automatically makes
the path an absolute one.
</member>
<member name="M:Poco.Path.setDevice(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="199">
Returns the node name.
</member>
<member name="M:Poco.Path.getDevice" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="202">
Sets the device name.
Setting a non-empty device automatically makes
the path an absolute one.
</member>
<member name="M:Poco.Path.depth" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="207">
Returns the device name.
</member>
<member name="M:Poco.Path.directory(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="210">
Returns the number of directories in the directory list.
</member>
<member name="M:Poco.Path.op_Subscript(System.Int32)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="213">
Returns the n'th directory in the directory list.
If n == depth(), returns the filename.
</member>
<member name="M:Poco.Path.pushDirectory(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="217">
Returns the n'th directory in the directory list.
If n == depth(), returns the filename.
</member>
<member name="M:Poco.Path.popDirectory" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="221">
Adds a directory to the directory list.
</member>
<member name="M:Poco.Path.popFrontDirectory" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="224">
Removes the last directory from the directory list.
</member>
<member name="M:Poco.Path.setFileName(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="227">
Removes the first directory from the directory list.
</member>
<member name="M:Poco.Path.getFileName" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="230">
Sets the filename.
</member>
<member name="M:Poco.Path.setBaseName(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="233">
Returns the filename.
</member>
<member name="M:Poco.Path.getBaseName" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="236">
Sets the basename part of the filename and
does not change the extension.
</member>
<member name="M:Poco.Path.setExtension(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="240">
Returns the basename (the filename sans
extension) of the path.
</member>
<member name="M:Poco.Path.getExtension" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="244">
Sets the filename extension.
</member>
<member name="M:Poco.Path.version" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="247">
Returns the filename extension.
</member>
<member name="M:Poco.Path.clear" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="250">
Returns the file version. VMS only.
</member>
<member name="M:Poco.Path.parent" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="253">
Clears all components.
</member>
<member name="M:Poco.Path.absolute" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="256">
Returns a path referring to the path's
directory.
</member>
<member name="M:Poco.Path.absolute(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="260">
Returns an absolute variant of the path,
taking the current working directory as base.
</member>
<member name="M:Poco.Path.forDirectory(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="264">
Returns an absolute variant of the path,
taking the given path as base.
</member>
<member name="M:Poco.Path.forDirectory(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path.Style)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="268">
Creates a path referring to a directory.
</member>
<member name="M:Poco.Path.separator" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="271">
Creates a path referring to a directory.
</member>
<member name="M:Poco.Path.pathSeparator" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="274">
Returns the platform's path name separator, which separates
the components (names) in a path. 

On Unix systems, this is the slash '/'. On Windows systems, 
this is the backslash '\'. On OpenVMS systems, this is the
period '.'.
</member>
<member name="M:Poco.Path.current" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="282">
Returns the platform's path separator, which separates
single paths in a list of paths.

On Unix systems, this is the colon ':'. On Windows systems,
this is the semicolon ';'. On OpenVMS systems, this is the
comma ','.
</member>
<member name="M:Poco.Path.home" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="290">
Returns the current working directory.
</member>
<member name="M:Poco.Path.configHome" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="293">
Returns the user's home directory.
</member>
<member name="M:Poco.Path.dataHome" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="296">
Returns the user's config directory.

On Unix systems, this is the '~/.config/'. On Windows systems,
this is '%APPDATA%'.
</member>
<member name="M:Poco.Path.cacheHome" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="302">
Returns the user's data directory.

On Unix systems, this is the '~/.local/share/'. On Windows systems,
this is '%APPDATA%'.
</member>
<member name="M:Poco.Path.temp" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="308">
Returns the user's cache directory.

On Unix systems, this is the '~/.cache/'. On Windows systems,
this is '%APPDATA%'.
</member>
<member name="M:Poco.Path.config" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="314">
Returns the temporary directory.
</member>
<member name="M:Poco.Path.null" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="317">
Returns the systemwide config directory.

On Unix systems, this is the '/etc/'.
</member>
<member name="M:Poco.Path.expand(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="322">
Returns the name of the null device.
</member>
<member name="M:Poco.Path.listRoots(std.vector&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.allocator&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="325">
Expands all environment variables contained in the path.

On Unix, a tilde as first character in the path is
replaced with the path to user's home directory.
</member>
<member name="M:Poco.Path.find(std._Vector_const_iterator&lt;std._Vector_val&lt;std._Simple_types&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;&gt;&gt;,std._Vector_const_iterator&lt;std._Vector_val&lt;std._Simple_types&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;&gt;&gt;,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.Co" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="331">
Fills the vector with all filesystem roots available on the
system. On Unix, there is exactly one root, "/".
On Windows, the roots are the drive letters.
On OpenVMS, the roots are the mounted disks.
</member>
<member name="M:Poco.Path.find(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Poco.Path*!System.Runtime.CompilerServices.IsImplicitlyDerefer" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="337">
Searches the file with the given name in the locations (paths) specified
by it and end. A relative path may be given in name.

If the file is found in one of the locations, the complete
path of the file is stored in the path given as argument and true is returned. 
Otherwise false is returned and the path argument remains unchanged.
</member>
<member name="M:Poco.Path.transcode(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="345">
Searches the file with the given name in the locations (paths) specified
in pathList. The paths in pathList must be delimited by the platform's
path separator (see pathSeparator()). A relative path may be given in name.

If the file is found in one of the locations, the complete
path of the file is stored in the path given as argument and true is returned. 
Otherwise false is returned and the path argument remains unchanged.
</member>
<member name="M:Poco.Path.parseUnix(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\path.h" line="354">
On Windows, if POCO has been compiled with Windows UTF-8 support 
(POCO_WIN32_UTF8), this function converts a string (usually containing a path) 
encoded in UTF-8 into a string encoded in the current Windows code page.

This function should be used for every string passed as a file name to
a string stream or fopen().

On all other platforms, or if POCO has not been compiled with Windows UTF-8
support, this function returns the string unchanged.
</member>
<member name="T:Poco.URI" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="35">
A Uniform Resource Identifier, as specified in RFC 3986.

The URI class provides methods for building URIs from their
parts, as well as for splitting URIs into their parts.
Furthermore, the class provides methods for resolving
relative URIs against base URIs.

The class automatically performs a few normalizations on
all URIs and URI parts passed to it:
  * scheme identifiers are converted to lower case
  * percent-encoded characters are decoded (except for the query string)
  * optionally, dot segments are removed from paths (see normalize())

Note that dealing with query strings requires some precautions, as, internally,
query strings are stored in percent-encoded form, while all other parts of the URI
are stored in decoded form. While parsing query strings from properly encoded URLs
generally works, explicitly setting query strings with setQuery() or extracting
query strings with getQuery() may lead to ambiguities. See the descriptions of
setQuery(), setRawQuery(), getQuery() and getRawQuery() for more information.
</member>
<member name="M:Poco.URI.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="59">
Creates an empty URI.
</member>
<member name="M:Poco.URI.#ctor(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="62">
Parses an URI from the given string. Throws a
SyntaxException if the uri is not valid.
</member>
<member name="M:Poco.URI.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="66">
Parses an URI from the given string. Throws a
SyntaxException if the uri is not valid.
</member>
<member name="M:Poco.URI.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices." decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="70">
Creates an URI from its parts.
</member>
<member name="M:Poco.URI.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices." decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="73">
Creates an URI from its parts.
</member>
<member name="M:Poco.URI.#ctor(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices." decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="76">
Creates an URI from its parts.
</member>
<member name="M:Poco.URI.#ctor(Poco.URI!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="79">
Creates an URI from its parts.
</member>
<member name="M:Poco.URI.#ctor(Poco.URI!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="82">
Copy constructor. Creates an URI from another one.
</member>
<member name="M:Poco.URI.#ctor(Poco.Path!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="85">
Creates an URI from a base URI and a relative URI, according to
the algorithm in section 5.2 of RFC 3986.
</member>
<member name="M:Poco.URI.Dispose" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="89">
Creates a URI from a path.

The path will be made absolute, and a file:// URI
will be built from it.
</member>
<member name="M:Poco.URI.op_Assign(Poco.URI!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="95">
Destroys the URI.
</member>
<member name="M:Poco.URI.op_Assign(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="98">
Assignment operator.
</member>
<member name="M:Poco.URI.op_Assign(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="101">
Parses and assigns an URI from the given string. Throws a
SyntaxException if the uri is not valid.
</member>
<member name="M:Poco.URI.swap(Poco.URI*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="105">
Parses and assigns an URI from the given string. Throws a
SyntaxException if the uri is not valid.
</member>
<member name="M:Poco.URI.clear" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="109">
Swaps the URI with another one.	
</member>
<member name="M:Poco.URI.toString" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="112">
Clears all parts of the URI.
</member>
<member name="M:Poco.URI.getScheme" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="115">
Returns a string representation of the URI.

Characters in the path, query and fragment parts will be 
percent-encoded as necessary.
</member>
<member name="M:Poco.URI.setScheme(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="121">
Returns the scheme part of the URI.
</member>
<!-- Discarding badly formed XML document comment for member 'M:Poco.URI.getUserInfo'. -->
<member name="M:Poco.URI.setUserInfo(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="131">
Returns the user-info part of the URI.
</member>
<member name="M:Poco.URI.getHost" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="134">
Sets the user-info part of the URI.
</member>
<member name="M:Poco.URI.setHost(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="137">
Returns the host part of the URI.
</member>
<member name="M:Poco.URI.getPort" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="140">
Sets the host part of the URI.
</member>
<member name="M:Poco.URI.setPort(System.UInt16)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="143">
Returns the port number part of the URI.

If no port number (0) has been specified, the
well-known port number (e.g., 80 for http) for
the given scheme is returned if it is known.
Otherwise, 0 is returned.
</member>
<member name="M:Poco.URI.getAuthority" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="151">
Sets the port number part of the URI.
</member>
<member name="M:Poco.URI.setAuthority(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="154">
Returns the authority part (userInfo, host and port)
of the URI. 

If the port number is a well-known port
number for the given scheme (e.g., 80 for http), it
is not included in the authority.
</member>
<member name="M:Poco.URI.getPath" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="162">
Parses the given authority part for the URI and sets
the user-info, host, port components accordingly.
</member>
<member name="M:Poco.URI.setPath(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="166">
Returns the decoded path part of the URI.
</member>
<member name="M:Poco.URI.getQuery" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="169">
Sets the path part of the URI.
</member>
<!-- Discarding badly formed XML document comment for member 'M:Poco.URI.setQuery(std.basic_string<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte>>!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)'. -->
<!-- Discarding badly formed XML document comment for member 'M:Poco.URI.addQueryParameter(std.basic_string<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte>>!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator<System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte>>!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)'. -->
<!-- Discarding badly formed XML document comment for member 'M:Poco.URI.getRawQuery'. -->
<member name="M:Poco.URI.setRawQuery(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="205">
Returns the query string in raw form, which usually
means percent encoded.
</member>
<member name="M:Poco.URI.getQueryParameters" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="209">
Sets the query part of the URI.

The given query string must be properly percent-encoded.
</member>
<member name="M:Poco.URI.setQueryParameters(std.vector&lt;std.pair&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;,std.allocator&lt;std.pair&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="214">
Returns the decoded query string parameters as a vector
of name-value pairs.
</member>
<member name="M:Poco.URI.getFragment" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="218">
Sets the query part of the URI from a vector
of query parameters.

Calls addQueryParameter() for each parameter name and value.
</member>
<member name="M:Poco.URI.setFragment(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="224">
Returns the fragment part of the URI.
</member>
<member name="M:Poco.URI.setPathEtc(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="227">
Sets the fragment part of the URI.
</member>
<member name="M:Poco.URI.getPathEtc" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="230">
Sets the path, query and fragment parts of the URI.
</member>
<member name="M:Poco.URI.getPathAndQuery" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="233">
Returns the encoded path, query and fragment parts of the URI.
</member>
<member name="M:Poco.URI.resolve(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="236">
Returns the encoded path and query parts of the URI.	
</member>
<member name="M:Poco.URI.resolve(Poco.URI!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="239">
Resolves the given relative URI against the base URI.
See section 5.2 of RFC 3986 for the algorithm used.
</member>
<member name="M:Poco.URI.isRelative" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="243">
Resolves the given relative URI against the base URI.
See section 5.2 of RFC 3986 for the algorithm used.
</member>
<member name="M:Poco.URI.empty" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="247">
Returns true if the URI is a relative reference, false otherwise.

A relative reference does not contain a scheme identifier.
Relative references are usually resolved against an absolute
base reference.
</member>
<member name="M:Poco.URI.op_Equality(Poco.URI!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="254">
Returns true if the URI is empty, false otherwise.
</member>
<member name="M:Poco.URI.op_Equality(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="257">
Returns true if both URIs are identical, false otherwise.

Two URIs are identical if their scheme, authority,
path, query and fragment part are identical.
</member>
<member name="M:Poco.URI.op_Inequality(Poco.URI!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="263">
Parses the given URI and returns true if both URIs are identical,
false otherwise.
</member>
<member name="M:Poco.URI.op_Inequality(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="267">
Returns true if both URIs are identical, false otherwise.
</member>
<member name="M:Poco.URI.normalize" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="270">
Parses the given URI and returns true if both URIs are identical,
false otherwise.
</member>
<member name="M:Poco.URI.getPathSegments(std.vector&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.allocator&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="274">
Normalizes the URI by removing all but leading . and .. segments from the path.

If the first path segment in a relative path contains a colon (:), 
such as in a Windows path containing a drive letter, a dot segment (./) 
is prepended in accordance with section 3.3 of RFC 3986.
</member>
<member name="M:Poco.URI.encode(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="281">
Places the single path segments (delimited by slashes) into the
given vector.
</member>
<member name="M:Poco.URI.decode(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="285">
URI-encodes the given string by escaping reserved and non-ASCII
characters. The encoded string is appended to encodedStr.
</member>
<member name="M:Poco.URI.equals(Poco.URI!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="289">
URI-decodes the given string by replacing percent-encoded
characters with the actual character. The decoded string
is appended to decodedStr.

When plusAsSpace is true, non-encoded plus signs in the query are decoded as spaces.
(http://www.w3.org/TR/html401/interact/forms.html#h-17.13.4.1)
</member>
<member name="M:Poco.URI.isWellKnownPort" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="298">
Returns true if both uri's are equivalent.
</member>
<member name="M:Poco.URI.getWellKnownPort" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="301">
Returns true if the URI's port number is a well-known one
(for example, 80, if the scheme is http).
</member>
<member name="M:Poco.URI.parse(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="305">
Returns the well-known port number for the URI's scheme,
or 0 if the port number is not known.
</member>
<member name="M:Poco.URI.parseAuthority(std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="309">
Parses and assigns an URI from the given string. Throws a
SyntaxException if the uri is not valid.
</member>
<member name="M:Poco.URI.parseHostAndPort(std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="313">
Parses and sets the user-info, host and port from the given data.
</member>
<member name="M:Poco.URI.parsePath(std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="316">
Parses and sets the host and port from the given data.
</member>
<member name="M:Poco.URI.parsePathEtc(std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="319">
Parses and sets the path from the given data.
</member>
<member name="M:Poco.URI.parseQuery(std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="322">
Parses and sets the path, query and fragment from the given data.
</member>
<member name="M:Poco.URI.parseFragment(std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std._String_const_iterator&lt;std._String_val&lt;std._Simple_types&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="325">
Parses and sets the query from the given data.
</member>
<member name="M:Poco.URI.mergePath(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="328">
Parses and sets the fragment from the given data.
</member>
<member name="M:Poco.URI.removeDotSegments(System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="331">
Appends a path to the URI's path.
</member>
<member name="M:Poco.URI.getPathSegments(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,std.vector&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.allocator&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runti" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="334">
Removes all dot segments from the path.
</member>
<member name="M:Poco.URI.buildPath(std.vector&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,std.allocator&lt;std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,System.Boolean,System.Boolean)" decl="true" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="337">
Places the single path segments (delimited by slashes) into the
given vector.
</member>
<member name="F:Poco.URI.RESERVED_PATH" decl="false" source="f:\projects\trader\deps\poco\foundation\include\poco\uri.h" line="341">
Builds the path from the given segments.
</member>
</members>
</doc>