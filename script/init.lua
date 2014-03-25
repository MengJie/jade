
print "hello, world!"

function test(a1, a2, a3, a4)
    print("hello, lua", a1, a2, a3, a4)
end

function test2()
    local foo = Foo()
    foo:init()
    foo:bar(5)
    foo = nil
    collectgarbage("collect")
    collectgarbage("collect")
end

