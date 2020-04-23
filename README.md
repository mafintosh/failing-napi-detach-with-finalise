# Failing n-api detach arraybuffer test in 12

Using Node.js 12.16.2

```
git clone git://github.com/mafintosh/failing-napi-detach-with-finalise
cd failing-napi-detach-with-finalise
npm install
node example.js
```

Running the above crashes with a V8 abort, even though the arraybuffer is externally
allocated.

Making an externally allocated buffer without a finaliser does not crash

```
node example-with-no-finalise.js
```

On Node 13+ this seems to be fine in both cases

## License

MIT
