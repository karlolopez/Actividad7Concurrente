var resolveAfter25Seconds = (func) => {
    console.log(`Empezando una promesa lenta en: ${func}`)
    return new Promise(resolve => {
        setTimeout(function() {
            resolve(25)
            console.log(`Promesa lenta terminada en: ${func}`)
        }, 25000)
    })
}

var resolveAfter1Second = (func) => {
    console.log(`Empezando promesa rápida: ${func}`)
    return new Promise(resolve => {
        setTimeout(function() {
            resolve(25)
            console.log(`Promesa rápida terminada en: ${func}`)
        }, 1000)
    })
}

var sequentialStart = async () => {
    console.log("---Comienzo sequencial---")
    const slow = await resolveAfter25Seconds('Comienzo sequencial')
    const fast = await resolveAfter1Second('Comienzo sequencial')
    console.log(slow + ' - Comienzo sequencial')
    console.log(fast + ' - Comienzo sequencial')
}

var concurrentStart = async () => {
    console.log("--- Comienzo concurrente ---")
    const slow = resolveAfter25Seconds('Comienzo concurrente')
    const fast = resolveAfter1Second('Comienzo concurrente')
    console.log(await slow + ' - Comienzo concurrente')
    console.log(await fast + ' - Comienzo concurrente')
}

var stillSerial = () => {
    console.log("-- Concurrente con Promise.then -- ")
    Promise.all([resolveAfter25Seconds('still serial'), resolveAfter1Second('still serial')]).then(([slow, fast]) => {
        console.log(slow + ' - still serial')
        console.log(fast + ' - still serial')
    })
}

var parallel = () => {
    console.log("-- Paralelo con promise.then")
    resolveAfter25Seconds('paralelo').then(message => { console.log(message + ' - paralelo') })
    resolveAfter1Second('paralelo').then(message => { console.log(message + ' - paralelo') })
}

sequentialStart()
setTimeout(function() {
    console.log('5 segundos después...')
    concurrentStart()
    }, 5000)
setTimeout(function() {
    console.log('10 segundos después...')
    stillSerial()
    }, 10000)
setTimeout(function() {
    console.log('15 segundos después...')
    parallel()
    }, 15000)