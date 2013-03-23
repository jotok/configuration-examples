fuzzy_string = "uo"
exact = "c"
date = "d"

config = {
    directory = ".",
    filea = "sorta.dat",
    fileb = "sortb.dat",
    verbose = false,
    summary = false,
    fields = {},
    strategies = {}
}

function directory(s)
    config.directory = s
end

function files(t)
    config.filea = t[1]
    config.fileb = t[2]
end

function flags(t)
    for k, v in pairs(t) do
        config[k] = v
    end
end

function fields(t)
    for i, f in ipairs(t) do
        name = f[1]
        table.remove(f, 1)
        config.fields[name] = f
    end
end

function strategy(t)
    table.insert(config.strategies, t)
end
