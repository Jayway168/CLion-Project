//
// Created by Jayway Timg pm 2022-09-28
//
interface State {
    name: string
    capital: string
}

const states: State[] = [
    { name: 'Alabama', capital: 'Montgomery' },
    { name: 'Alaska', capital: 'Juneau' },
    { name: 'Arizona', capital: 'Phoenix' },
]

for (const state of states) {
    console.log(state.capital)
}

let greet: string = 'Greetings'
let geeks: string = 'GeeksforGeeks'
console.log(greet + ' from ' + geeks)
