
print "hello, world!"

function test(a1, a2, a3, a4)
    print("hello, lua", a1, a2, a3, a4)
end

function test2()
    local foo = Foo(5, 6, 7)
    local mt = debug.getmetatable(foo)
    foo:foo()
    print(foo:bar(55))
    foo:foo()
    foo = nil
    collectgarbage("collect")
    collectgarbage("collect")
end

