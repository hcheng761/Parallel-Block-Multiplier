
mymult_make
maxerr = 0 ;

for m = 1:10
    for n = 1:10
        for k = 1:10
            A = rand (m, k) ;
            B = rand (k, n) ;
            C = rand (m, n) ;
            D = C + 100*A*B ;
            D2 = mymult (C, A,B, 100) ;
            err = norm (D-D2,1) ;
            if (err > 1e-10)
                error ('!')
            end
            maxerr = max (maxerr, err) ;
        end
    end
end

maxerr
pause

% now find the cache size

maxerr = 0 ;
figure (3)

Nset = [1:200 210:10:1100 1200:100:2000] ;
Result = nan (1,length (Nset)) ;

for kk = 1:length (Nset) ;
    n = Nset (kk) ;
    A = rand (n,n) ;
    B = rand (n,n) ;
    C = rand (n,n) ;

    flopcount = 2*n^3 ;
    ntrials = ceil (1e6 / flopcount) ;
    ntrials = min (ntrials, 1000) ;
    ntrials = max (ntrials, 1) ;

    tic
    D = mymult (C,A,B,ntrials) ;
    t = toc ;
    t = t / ntrials ;
    gflop = (flopcount / t) * 1e-9 ;

    fprintf ('n %4d  ntrials %4d Gflop %10.6f\n', n, ntrials, gflop) ;
    Result (kk) = gflop ;

    D2 = C+ntrials*A*B ;
    err = norm (D-D2,1) / norm (D,1) ;
    if (err > 1e-10)
        error ('!')
    end
    maxerr = max (maxerr, err) ;

    plot (Nset, Result, 'o') ;
    drawnow
end

maxerr



